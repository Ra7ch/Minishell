/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-zeh <mben-zeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:42:11 by mben-zeh          #+#    #+#             */
/*   Updated: 2023/06/25 03:43:31 by mben-zeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_builtins(t_data *data)
{
	if (data->arg)
	{
		if (!ft_strcmp("echo", data->arg[0]))
			return (1);
		else if (!ft_strcmp("pwd", data->arg[0]))
			return (2);
		else if (!ft_strcmp("env", data->arg[0]))
			return (3);
		else if (!ft_strcmp("export", data->arg[0]))
			return (4);
		else if (!ft_strcmp("cd", data->arg[0]))
			return (5);
		else if (!ft_strcmp("unset", data->arg[0]))
			return (6);
		else if (!ft_strcmp("exit", data->arg[0]))
			return (7);
	}
	return (0);
}

char	*ft_getpwd(t_env *env)
{
	while (env)
	{
		if (!ft_strcmp(env->var, "PWD"))
			return (ft_strdup(env->value));
		env = env->next;
	}
	return (NULL);
}

void	ft_builtins_sub(char **str, t_env **env, t_data *data, int x)
{
	if (x == 1)
		ft_echo(&data->arg[1]);
	else if (x == 2)
	{
		*str = getcwd(NULL, 0);
		if (!(*str))
		{
			free(*str);
			*str = ft_getpwd(*env);
		}
		ft_putstr(*str, 1);
		ft_putstr("\n", 1);
		free(*str);
		g_v->exit_status = 0;
	}
}

int	ft_builtins(t_data *data, t_env **env, int x)
{
	char	*str;

	str = NULL;
	if (x == 1 || x == 2)
		ft_builtins_sub(&str, env, data, x);
	else if (x == 3)
	{
		if (data->arg[1])
			return (perror(data->arg[1]), g_v->exit_status = 127, 1);
		ft_env(*env, 0);
	}
	else if (x == 4)
	{
		if (!data->arg[1])
			ft_env(*env, 1);
		else
			ft_export(env, &data->arg[1]);
	}
	else if (x == 5)
		ft_cd(data, env);
	else if (x == 6)
		ft_unset(env, &data->arg[1], *env, *env);
	else if (x == 7)
		ft_exit(&data->arg[1]);
	return (0);
}
