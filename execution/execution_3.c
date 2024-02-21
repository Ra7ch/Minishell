/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-zeh <mben-zeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 00:30:51 by raitmous          #+#    #+#             */
/*   Updated: 2023/06/25 03:41:59 by mben-zeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

void	ft_msg_cmd_error(char *cmd)
{
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(": command not found\n", 2);
}

int	size_env(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		if (env->value)
			i++;
		env = env->next;
	}
	return (i);
}

char	**ft_env_tab(t_env *env)
{
	char	**ptr;
	int		i;
	int		len;

	i = 0;
	len = size_env(env);
	ptr = malloc(sizeof(char *) * (len + 1));
	while (i < len)
	{
		if (env->var && env->value)
		{
			ptr[i] = ft_strjoin(ft_strdup(env->var), "=");
			ptr[i] = ft_strjoin(ptr[i], env->value);
			i++;
		}
		env = env->next;
	}
	ptr[i] = NULL;
	return (ptr);
}

char	*ft_envchr(char **envp, char *str)
{
	int	i;

	i = 0;
	if (!envp || !str)
		return (NULL);
	while (envp[i])
	{
		if (!ft_strcmp(envp[i], str))
			return (envp[i]);
		i++;
	}
	return (NULL);
}
