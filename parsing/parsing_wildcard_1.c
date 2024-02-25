/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_wildcard_1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raitmous <raitmous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 01:08:14 by raitmous          #+#    #+#             */
/*   Updated: 2023/06/25 02:31:16 by raitmous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	look_for_quote(char *s, int *i, char c)
{
	while (s[*i])
	{
		(*i)++;
		if (s[*i] == c)
		{
			(*i)++;
			return ;
		}
	}
	return ;
}

int	check_wildcard(char *arg)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (arg[i])
	{
		if (arg[i] == 39 || arg[i] == 34)
		{
			look_for_quote(arg, &i, arg[i]);
			continue ;
		}
		else if (arg[i] == '*')
		{
			x = 1;
			i++;
			break ;
		}
		i++;
	}
	if (x == 1)
		return (1);
	return (0);
}

void	creat_word(char c, t_word **p, int type, int i)
{
	static t_word	*first;

	if (i == 0)
	{
		*p = malloc(sizeof(t_word));
		first = *p;
	}
	else
	{
		while ((*p)->next)
			(*p) = (*p)->next;
		(*p)->next = malloc(sizeof(t_word));
		(*p) = (*p)->next;
	}
	(*p)->c = c;
	(*p)->type = type;
	(*p)->next = NULL;
	*p = first;
}

int	token_word_sub(int *type, int *i, char *str)
{
	if (str[*i] == '\"' && (*type) == STATE_NORMAL)
	{
		(*type) = STATE_DOUBLE_QUOTE;
		(*i)++;
		return (0);
	}
	else if (str[*i] == '\"' && (*type) == STATE_DOUBLE_QUOTE)
	{
		(*type) = STATE_NORMAL;
		(*i)++;
		return (0);
	}
	if (str[*i] == '\'' && (*type) == STATE_NORMAL)
	{
		(*type) = STATE_SINGLE_QUOTE;
		(*i)++;
		return (0);
	}
	else if (str[*i] == '\'' && (*type) == STATE_SINGLE_QUOTE)
	{
		(*type) = STATE_NORMAL;
		(*i)++;
		return (0);
	}
	return (1);
}

t_word	*token_words(char *str)
{
	t_word	*p;
	int		i;
	int		type;
	int		j;

	j = 0;
	i = 0;
	p = NULL;
	type = STATE_NORMAL;
	while (str[i])
	{
		if (token_word_sub(&type, &i, str) == 0)
			continue ;
		creat_word(str[i], &p, type, j);
		i++;
		j++;
	}
	return (p);
}
