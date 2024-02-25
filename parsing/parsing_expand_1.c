/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expand_1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raitmous <raitmous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:33:15 by mben-zeh          #+#    #+#             */
/*   Updated: 2023/06/25 03:28:29 by raitmous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_quote(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\"' || str[i] == '\'')
		{
			return (1);
		}
		i++;
	}
	return (0);
}

int	check_expand(char *str, int use)
{
	int	i;
	int	quote;
	int	dquote;

	i = 0;
	quote = 0;
	dquote = 0;
	while (str[i])
	{
		if (use)
		{
			if (str[i] == '\"' && !(quote % 2))
				dquote++;
			else if (str[i] == '\'' && !(dquote % 2))
				quote++;
		}
		if (str[i] == '$' && !(quote % 2))
			return (1);
		i++;
	}
	return (0);
}

char	*get_expand(t_env *env, char *str)
{
	if (!str || !*str)
		return (ft_strdup("$"));
	if (!ft_strcmp(str, "?"))
	{
		return (free(str), ft_itoa(g_v->exit_status));
	}
	while (env && str)
	{
		if (!ft_strcmp(str, env->var))
			return (free(str), ft_strdup(env->value));
		env = env->next;
	}
	return (free(str), NULL);
}

void	inter_expand(char **str, char **string, t_env *env, int use)
{
	char	*expand;
	int		i;

	i = -1;
	expand = NULL;
	if ((*str)[1] == '?' || ft_isdigit((*str)[1]))
		expand = ft_strjoin(expand, (char []){*(++(*str)), 0});
	else
	{
		while (&str[0][1])
		{
			if ((!ft_isalpha((*str)[1]) && !ft_isdigit((*str)[1])
					&& (*str)[1] != '_' && (*str)[1] != '~'))
				break ;
			expand = ft_strjoin(expand, (char []){(*str)[1], 0});
			(*str)++;
		}
	}
	expand = get_expand(env, expand);
	while (use && expand && expand[++i])
		if (expand[i] == '\"' || expand[i] == '\'')
			expand[i] -= 29;
	*string = ft_strjoin(*string, expand);
	free(expand);
}

char	*ft_expand(char *str, t_env *env, int use)
{
	int		quote;
	int		dquote;
	char	*string;

	quote = 0;
	dquote = 0;
	string = NULL;
	while (*str)
	{
		if (use)
		{
			if (*str == '\"' && !(quote % 2))
				dquote++;
			else if (*str == '\'' && !(dquote % 2))
				quote++;
		}
		if (*str == '$' && !(quote % 2))
			inter_expand(&str, &string, env, use);
		else
			string = ft_strjoin(string, (char []){*str, 0});
		str++;
	}
	return (string);
}
