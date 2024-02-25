/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-zeh <mben-zeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 01:28:53 by raitmous          #+#    #+#             */
/*   Updated: 2023/06/25 03:44:04 by mben-zeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_unset_sub(t_env **env)
{
	(*env)->next = NULL;
	if ((*env)->value)
		free((*env)->value);
	if ((*env)->var)
		free((*env)->var);
	(*env)->value = NULL;
	(*env)->var = NULL;
	free((*env));
	(*env) = NULL;
}

void	ft_unset(t_env **env, char **str, t_env *node, t_env *temp)
{
	int	i;

	i = 0;
	g_v->exit_status = 0;
	while (str && str[i])
	{
		if (!ft_strcmp("_", str[i]) && ++i)
			continue ;
		if (is_var(str[i], &(int){0}, &(int){0}))
			return (ft_export_error(str, i, 0));
		while (*env)
		{
			if (!ft_strcmp((*env)->var, str[i]))
			{
				node->next = (*env)->next;
				ft_unset_sub(env);
				break ;
			}
			node = (*env);
			(*env) = (*env)->next;
		}
		*env = temp;
		i++;
	}
}

int	ft_is_number(char *str)
{
	int	i;

	i = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i])
		return (1);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (1);
		i++;
	}
	return (0);
}

void	ft_exit(char **arg)
{
	int	i;

	i = 0;
	if (!g_v->exit_inpipe)
		printf("exit\n");
	if (arg && !*arg)
		exit(g_v->exit_status);
	while (arg && arg[i])
	{
		if (i)
		{
			ft_putstr("exit: too many arguments\n", 2);
			g_v->exit_status = 1;
			return ;
		}
		if (ft_is_number(arg[i]))
		{
			ft_putstr("exit: ", 2);
			ft_putstr(arg[i], 2);
			ft_putstr("numeric argument required", 2);
			exit(255);
		}
		i++;
	}
	exit(ft_atoi(arg[0]));
}

void	ft_env(t_env *env, int is_export)
{
	while (env)
	{
		if (is_export || env->value)
		{
			if (is_export)
			{
				printf("declare -x %s", env->var);
				if (env->value)
					printf("=\"%s\"", env->value);
			}
			else if (env->value)
				printf("%s=%s", env->var, env->value);
			printf("\n");
		}
		env = env->next;
	}
	g_v->exit_status = 0;
}
