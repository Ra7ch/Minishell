/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-zeh <mben-zeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 01:17:03 by raitmous          #+#    #+#             */
/*   Updated: 2023/06/25 03:43:42 by mben-zeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cd_sub_sub(int *n, char **str, char *arg, t_env **env)
{
	char	*path;

	if (!ft_strcmp(arg, "-"))
	{
		path = ft_search_env(*env, "OLDPWD");
		*n = chdir(path);
		if (*n == 0)
		{
			*str = getcwd(NULL, 0);
			printf("%s\n", *str);
		}
		else
		{
			if (!path)
				ft_putstr("cd: OLDPWD not set\n", 2);
			else
				perror(path);
			*n = -2;
		}
		free(*str);
	}
	else if (!ft_strcmp(arg, "~"))
		*n = chdir(getenv("HOME"));
	else
		*n = chdir(arg);
}

void	ft_cd_sub1(int *n, char **str, char *arg, t_env **env)
{
	if (arg && ft_strcmp(arg, "--"))
		ft_cd_sub_sub(n, str, arg, env);
	else
	{
		*n = chdir(ft_search_env(*env, "HOME"));
		if (*n < 0)
		{
			ft_putstr("cd: HOME not set\n", 2);
			*n = -2;
		}
	}
}

void	ft_cd_sub2(char **str, t_env **env)
{
	*str = getcwd(NULL, 0);
	if (*str)
	{
		ft_search_inset(*env, (char *[]){"OLDPWD", ft_strdup(ft_search_env(*env,
					"PWD"))}, 1, 0);
		ft_search_inset(*env, (char *[]){"PWD", ft_strdup(*str)}, 1, 0);
	}
	else
		perror("cd :");
	free(*str);
}

void	ft_cd(t_data *data, t_env **env)
{
	int		n;
	char	*str;

	str = NULL;
	n = 0;
	ft_cd_sub1(&n, &str, data->arg[1], env);
	if (n == 0)
		ft_cd_sub2(&str, env);
	else
	{
		if (n != -2)
			perror(data->arg[1]);
		g_v->exit_status = 1;
		return ;
	}
	g_v->exit_status = 0;
}
