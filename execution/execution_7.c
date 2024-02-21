/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_7.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-zeh <mben-zeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 00:35:20 by raitmous          #+#    #+#             */
/*   Updated: 2023/06/25 03:42:41 by mben-zeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_execution_sub3(t_data *data, t_env **env, int *par)
{
	if (*par >= 2)
		exit(1);
	else if (data->token == TOKEN_AND)
	{
		*par = 0;
		ft_exection(data->left, env);
		if (g_v.exit_status == 0)
			ft_exection(data->right, env);
	}
	else if (data->token == TOKEN_OR)
	{
		*par = 0;
		ft_exection(data->left, env);
		if (g_v.exit_status != 0)
			ft_exection(data->right, env);
	}
	else if (!data->left && !data->right)
	{
		*par = 0;
		if (ft_exec(data, env))
			exit(1);
	}
}

int	ft_execution_sub0(t_data *data, int par)
{
	if (!data)
	{
		if (par >= 2)
		{
			if (par > 2)
				ft_putstr(ERROR_SYNTAX, 2);
			exit(1);
		}
		return (0);
	}
	return (1);
}

void	ft_exection(t_data *data, t_env **env)
{
	static int	par;
	int			*fd;
	int			pfd[2];
	pid_t		pid[2];

	fd = NULL;
	if (ft_execution_sub0(data, par) == 0)
		return ;
	ft_openfile(data, *env);
	if (data->token == TOKEN_PAR)
	{
		if (ft_execution_sub1(&data, env, &par, pfd) == 0)
			return ;
	}
	else if (data->token == TOKEN_PIPE)
	{
		if (ft_execution_sub2(&data, env, &par, pid) == 0)
			return ;
	}
	else if (data->token == TOKEN_AND || data->token == TOKEN_OR || (!data->left
			&& !data->right))
		ft_execution_sub3(data, env, &par);
}

char	*ft_getenv(t_env *env, const char *find)
{
	while (env)
	{
		if (!ft_strcmp(env->var, find))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}
