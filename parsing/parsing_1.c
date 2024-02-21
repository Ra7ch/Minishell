/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raitmous <raitmous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:36:31 by mben-zeh          #+#    #+#             */
/*   Updated: 2023/06/25 03:20:27 by raitmous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_add_list(char *str, t_list **list, int **all, t_env *env)
{
	int	i;

	i = *all[2];
	if (str[i] && is_token(str[i]) && !(*all[1] % 2) && !(*all[0] % 2))
	{
		while (*all[2] == 0 && is_token(str[i]) && str[i] == *str && i < 2)
		{
			if ((str[i] == '(' || str[i] == ')') && ++i)
				break ;
			i++;
		}
		ft_lstadd_back(list, ft_lstnew(ft_substr(str, 0, i)), env);
		str = &str[i];
		*all[2] = -1;
	}
	else if (!str[i + 1])
	{
		ft_lstadd_back(list, ft_lstnew(ft_substr(str, 0, i + (!str[i + 1]
						&& str[i] != ' '))), env);
		str = &str[i + (!str[i + 1])];
		*all[2] = -1;
	}
	return (str);
}

int	ft_spl_sub1(char **str, int *par, int (*qte)[3], int i)
{
	while ((*(*str) == ' ' || *(*str) == '\t') && (*str)++)
		;
	if (!*(*str))
		return (0);
	if (*(*str) == '(' && !((*qte)[1] % 2) && !((*qte)[0] % 2))
		(*par)++;
	else if (*(*str) == ')' && !((*qte)[1] % 2) && !((*qte)[0] % 2))
		(*par)--;
	if ((*par) < 0)
		return (1);
	if ((*str)[i] == '\"' && !((*qte)[1] % 2))
		(*qte)[0]++;
	else if ((*str)[i] == '\'' && !((*qte)[0] % 2))
		(*qte)[1]++;
	return (1);
}

int	ft_spl(char *str, t_list **list, t_env *env)
{
	int	i;
	int	qte[3];
	int	par;

	qte[0] = 0;
	qte[1] = 0;
	par = 0;
	i = -1;
	while (str[++i])
	{
		if (ft_spl_sub1(&str, &par, &qte, i) == 0)
			break ;
		str = ft_add_list(str, list, (int *[]){&qte[0], &qte[1], &i}, env);
	}
	return ((qte[1] % 2) || (qte[0] % 2) || par);
}

void	ft_add_env(t_env **data, char **env)
{
	if ((!ft_strcmp(env[0], "_") || !ft_strcmp(env[0], "OLDPWD")))
	{
		free(env[1]);
		env[1] = NULL;
	}
	ft_envadd_back(data, ft_envnew(env[0], env[1]));
	if (env)
		free(env);
}

void	ft_full_env(t_env **data, char **envp, char **env)
{
	int	i;
	int	j;

	i = 0;
	if (!envp)
		return ;
	while (envp[i])
	{
		j = 0;
		while (envp[i][j])
		{
			if (envp[i][j] == '=')
			{
				envp[i][j] = 3;
				break ;
			}
			j++;
		}
		env = ft_split(envp[i], 3);
		envp[i][j] = '=';
		ft_add_env(data, env);
		i++;
	}
}
