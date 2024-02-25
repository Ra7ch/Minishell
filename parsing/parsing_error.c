/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-zeh <mben-zeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:32:53 by mben-zeh          #+#    #+#             */
/*   Updated: 2023/06/25 05:39:00 by mben-zeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_check_error_sub1(t_list *list)
{
	if (list->prev)
	{
		if ((list->prev->token == FILE_IN || list->prev->token == FILE_OUT
				|| list->prev->token == WORD_LIM
				|| list->prev->token == TOKEN_WORD))
			return (ft_putstr(ERROR_SYNTAX, 2), g_v->exit_status = 258, (1));
	}
	return (0);
}

int	ft_check_error_sub2(t_list *list)
{
	if (list->prev)
	{
		if ((list->prev->token == TOKEN_PIPE || list->prev->token == TOKEN_AND
				|| list->prev->token == TOKEN_OR))
			return (ft_putstr(ERROR_SYNTAX, 2), g_v->exit_status = 258, (1));
		if (!ft_strcmp(list->prev->content, "(") && (!list->next
				|| ft_strcmp(list->next->content, ")")))
			return (ft_putstr(ERROR_SYNTAX, 2), g_v->exit_status = 258, (1));
	}
	if (list->next)
	{
		if (!ft_strcmp(list->next->content, "(")
			|| list->next->token == TOKEN_WORD)
			return (ft_putstr(ERROR_SYNTAX, 2), g_v->exit_status = 258, (1));
	}
	return (0);
}

int	ft_check_error_sub3(t_list *list, t_list *next, t_list *prev)
{
	if (list->token == TOKEN_PIPE || list->token == TOKEN_AND
		|| list->token == TOKEN_OR)
	{
		if (!next || !prev || !ft_strcmp(next->content, ")")
			|| !ft_strcmp(prev->content, "(") || !ft_strcmp(prev->content, "&")
			|| !ft_strcmp(next->content, "&"))
			return (ft_putstr(ERROR_SYNTAX, 2), g_v->exit_status = 258, (1));
		else if (prev->token == TOKEN_PIPE || prev->token == TOKEN_AND
			|| prev->token == TOKEN_OR)
			return (ft_putstr(ERROR_SYNTAX, 2), g_v->exit_status = 258, (1));
	}
	else if (list->token == TOKEN_INPUT || list->token == TOKEN_APPEND
		|| list->token == TOKEN_OUTPUT || list->token == TOKEN_HEREDOC)
	{
		if (next)
		{
			if (next->token != FILE_IN && next->token != FILE_OUT
				&& next->token != FILE_APP && next->token != WORD_LIM)
				return (ft_putstr(ERROR_SYNTAX, 2), g_v->exit_status = 258, (1));
		}
		else
			return (ft_putstr(ERROR_SYNTAX, 2), (1));
	}
	return (0);
}

int	ft_check_error(t_list *list)
{
	if (list->token == TOKEN_PAR)
	{
		if (!ft_strcmp(list->content, "("))
		{
			if (ft_check_error_sub1(list) == 1)
				return (1);
		}
		else
		{
			if (ft_check_error_sub2(list) == 1)
				return (1);
		}
	}
	else if (list->token == TOKEN_PIPE || list->token == TOKEN_AND
		|| list->token == TOKEN_OR || list->token == TOKEN_INPUT
		|| list->token == TOKEN_APPEND || list->token == TOKEN_OUTPUT
		|| list->token == TOKEN_HEREDOC)
	{
		if (ft_check_error_sub3(list, list->next, list->prev) == 1)
			return (1);
	}
	return (0);
}

int	ft_check_redir(t_list *list)
{
	if (list->next)
	{
		if (list->next->token != FILE_IN && list->next->token != FILE_OUT
			&& list->next->token != FILE_APP && list->next->token != WORD_LIM)
		{
			ft_putstr("syntax error near unexpected token `", 2);
			ft_putstr(list->next->content, 2);
			ft_putstr("'", 2);
			g_v->exit_status = 258;
			return (1);
		}
		else
		{
			return (0);
		}
	}
	else
		return (ft_putstr("syntax error near unexpected token `newline'", 2),
			(0));
}
