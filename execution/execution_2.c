/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-zeh <mben-zeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 00:16:20 by raitmous          #+#    #+#             */
/*   Updated: 2023/06/25 03:40:33 by mben-zeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_args_sub3(char **temp, char **ptr)
{
	*temp = ft_quote(*ptr);
	if (!*(*temp))
	{
		free(*temp);
		*temp = ft_strdup((char []){127, 0});
	}
	free(*ptr);
	*ptr = *temp;
}

void	ft_args_sub2(t_env *env, char **temp, char **ptr)
{
	if (check_expand(*ptr, 1) || !ft_strcmp(*ptr, "~"))
	{
		if (!ft_strcmp(*ptr, "~"))
		{
			free((*ptr));
			(*ptr) = ft_strdup(getenv("HOME"));
		}
		else
		{
			(*temp) = ft_expand((*ptr), env, 1);
			free((*ptr));
			(*ptr) = (*temp);
		}
	}
	if ((*ptr) && check_wildcard((*ptr)))
	{
		(*temp) = (*ptr);
		(*ptr) = expand_wildcard((*ptr));
		if ((*ptr))
			free((*temp));
		else
			(*ptr) = (*temp);
	}
	if (*ptr)
		*ptr = ft_split_join(*ptr, env);
}

void	ft_args_sub1(char **arg, t_env *env, char **str)
{
	int		i;
	int		j;
	char	*temp;
	char	*ptr;

	i = 0;
	j = -1;
	while (arg[i])
	{
		temp = NULL;
		ptr = ft_strdup(arg[i]);
		ft_args_sub2(env, &temp, &ptr);
		if (check_quote(arg[i]))
			ft_args_sub3(&temp, &ptr);
		while (ptr && ptr[++j])
			if (ptr[j] == 5 || ptr[j] == 10)
				ptr[j] += 29;
		if (ptr)
		{
			*str = ft_strjoin(ft_strjoin(*str, (char []){3, 0}), ptr);
			free(ptr);
		}
		i++;
	}
}

void	ft_arg_while(char **args)
{
	int	i;

	i = 0;
	while (args && args[i])
	{
		if (!ft_strcmp(args[i], (char []){127, 0}))
			args[i][0] = 0;
		i++;
	}
}

char	**ft_args(char **arg, t_env *env)
{
	char	*str;
	char	**args;

	str = NULL;
	args = NULL;
	ft_args_sub1(arg, env, &str);
	if (str)
		return (args = ft_split(str, 3), free(str), ft_arg_while(args), args);
	return (NULL);
}
