/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raitmous <raitmous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 01:23:12 by raitmous          #+#    #+#             */
/*   Updated: 2023/06/25 02:29:30 by raitmous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_search_insert_sub(t_env **env, char ***str, int equal, int add)
{
	if ((*str)[1])
	{
		if ((*env)->value && !add)
			free((*env)->value);
		if (add)
		{
			(*env)->value = ft_strjoin((*env)->value, (*str)[1]);
			free((*str)[1]);
		}
		else
			(*env)->value = (*str)[1];
	}
	else if (equal)
	{
		if ((*env)->value)
			free((*env)->value);
		(*env)->value = ft_strdup("");
	}
}

int	ft_search_inset(t_env *env, char **str, int equal, int add)
{
	while (env)
	{
		if (!ft_strcmp(env->var, str[0]))
		{
			ft_search_insert_sub(&env, &str, equal, add);
			return (0);
		}
		env = env->next;
	}
	return (1);
}

char	*ft_search_env(t_env *env, char *str)
{
	while (env)
	{
		if (!ft_strcmp(env->var, str))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

void	ft_export_error(char **str, int i, int is_export)
{
	if (is_export)
		ft_putstr("export: `", 2);
	else
		ft_putstr("unset: `", 2);
	ft_putstr(str[i], 2);
	ft_putstr("': not a valid identifier\n", 2);
	g_v->exit_status = 1;
}

void	ft_export(t_env **env, char **str)
{
	int		i;
	char	**arg;
	int		equal;
	int		add;

	add = 0;
	i = 0;
	g_v->exit_status = 0;
	while (str[i])
	{
		equal = 0;
		if (!is_var(str[i], &equal, &add))
		{
			arg = ft_split(str[i], 3);
			if (ft_search_inset(*env, arg, equal, add))
				ft_envadd_back(env, ft_envnew(arg[0], arg[1]));
			else
				free(arg[0]);
			free(arg);
		}
		else
			ft_export_error(str, i, 1);
		i++;
	}
}
