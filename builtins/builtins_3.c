/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-zeh <mben-zeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 01:17:03 by raitmous          #+#    #+#             */
/*   Updated: 2023/06/25 03:43:54 by mben-zeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_n(char *str)
{
	int	i;

	i = 0;
	if (str[i++] != '-')
		return (1);
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

void	ft_echo(char **str)
{
	int	n;
	int	i;

	n = 0;
	while (str[n] && !ft_check_n(str[n]))
		n++;
	i = n;
	while (str[i])
	{
		ft_putstr(str[i], 1);
		if (str[i + 1])
			ft_putstr(" ", 1);
		i++;
	}
	if (!n)
		ft_putstr("\n", 1);
	g_v.exit_status = 0;
}

int	is_var(char *str, int *equal, int *add)
{
	int	i;

	i = 0;
	if (!ft_isalpha(str[i]) && str[i] != '_')
		return (1);
	while (str[i])
	{
		if (!ft_isalpha(str[i]) && !ft_isdigit(str[i]) && str[i] != '='
			&& str[i] != '_' && !*equal && str[i] != '+')
			return (1);
		if (!*equal && str[i] == '+' && str[i + 1] != '=')
			return (1);
		if (!*equal && str[i] == '+' && str[i + 1] == '=')
		{
			*add = 1;
			str[i] = 3;
		}
		if (!*equal && str[i] == '=')
		{
			*equal = 1;
			str[i] = 3;
		}
		i++;
	}
	return (0);
}

int	ft_strcmp2(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	ft_underscore(t_env *env, char *value)
{
	while (env)
	{
		if (env->var && !ft_strcmp(env->var, "_"))
		{
			if (env->value)
			{
				free(env->value);
				env->value = NULL;
			}
			env->value = ft_strdup(value);
			return (1);
		}
		env = env->next;
	}
	return (0);
}
