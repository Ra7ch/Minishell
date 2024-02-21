/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_4.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-zeh <mben-zeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 00:31:51 by raitmous          #+#    #+#             */
/*   Updated: 2023/06/25 03:41:50 by mben-zeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**ft_path_envp(t_env *envp)
{
	char	*env;
	char	**path;
	int		i;

	i = 0;
	path = NULL;
	env = ft_getenv(envp, "PATH");
	if (!env)
		return (0);
	env = ft_substr(env, 0, ft_strlen(env));
	path = ft_split(env, ':');
	while (path[i])
	{
		path[i] = ft_strjoin(path[i], "/");
		i++;
	}
	free(env);
	return (path);
}

int	ft_charexist(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] || !(char)c)
	{
		if (s[i] == (char)c)
			return (1);
		i++;
	}
	return (0);
}

void	ft_isdir(char **str, char **envp)
{
	struct stat	filestat;

	lstat(str[0], &filestat);
	if (S_ISDIR(filestat.st_mode))
	{
		(ft_putstr(str[0], 2), ft_putstr(": is a directory\n", 2), exit(126));
	}
	else
	{
		if (!access(str[0], F_OK))
		{
			if (!access(str[0], X_OK) && !access(str[0], R_OK))
			{
				if (execve(str[0], str, envp) < 0)
					(perror(str[0]), exit(127));
			}
			else
				(perror(str[0]), exit(126));
		}
		else
			(perror(str[0]), exit(127));
	}
}

void	ft_exec_cmd(t_data *data, t_env *env)
{
	int		i;
	char	*path;
	char	**envp;

	i = 0;
	if (!data->arg || !*data->arg)
	{
		if (data->arg)
			(ft_msg_cmd_error(data->arg[0]), exit(127));
		exit(0);
	}
	if (data->arg && !ft_strcmp(data->arg[0], "exit"))
		return ;
	envp = ft_env_tab(env);
	if (ft_charexist(data->arg[0], '/'))
		ft_isdir(data->arg, envp);
	data->path = ft_path_envp(env);
	if (!data->path)
		(ft_msg_cmd_error(data->arg[0]), exit(127));
	while (data->path[i])
	{
		path = ft_strjoin(ft_strdup(data->path[i++]), data->arg[0]);
		(execve(path, data->arg, envp), free(path));
	}
	(ft_msg_cmd_error(data->arg[0]), exit(127));
}

int	ft_exec_sub1(t_data **data, t_env **env)
{
	int	i;

	i = 0;
	if ((*data)->arg && *(*data)->arg)
	{
		(*data)->arg = ft_args((*data)->arg, *env);
		while ((*data)->arg && (*data)->arg[i])
			i++;
		if (i > 0)
		{
			if (!ft_underscore(*env, (*data)->arg[i - 1]))
				ft_envadd_back(env, ft_envnew(ft_strdup("_"),
						ft_strdup((*data)->arg[i - 1])));
		}
		else
			ft_envadd_back(env, ft_envnew(ft_strdup("_"), NULL));
		if (!(*data)->arg)
			return (0);
	}
	else
	{
		if (!ft_underscore(*env, NULL))
			ft_envadd_back(env, ft_envnew(ft_strdup("_"), NULL));
	}
	return (1);
}
