/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_expand_2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raitmous <raitmous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 01:51:48 by raitmous          #+#    #+#             */
/*   Updated: 2023/06/25 03:28:52 by raitmous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_quote(char *str)
{
	char	*ptr;
	int		quote;
	int		dquote;

	ptr = ft_strdup("");
	quote = 0;
	dquote = 0;
	while (*str)
	{
		if (*str == '\"' && !(quote % 2))
			dquote++;
		else if (*str == '\'' && !(dquote % 2))
			quote++;
		if (*str == '\"' || *str == '\'')
		{
			if ((*str == '\"' && (quote % 2)) || (*str == '\'' && (dquote % 2)))
				ptr = ft_strjoin(ptr, (char []){*str, 0});
		}
		else
			ptr = ft_strjoin(ptr, (char []){*str, 0});
		str++;
	}
	return (ptr);
}
