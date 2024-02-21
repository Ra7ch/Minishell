/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raitmous <raitmous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 01:36:17 by raitmous          #+#    #+#             */
/*   Updated: 2023/06/25 02:31:40 by raitmous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_token_file(t_list *node, t_list *new, t_env *env)
{
	char	*ptr;

	(void)env;
	ptr = NULL;
	if (node->token == TOKEN_APPEND)
		new->token = FILE_APP;
	else if (node->token == TOKEN_INPUT)
		new->token = FILE_IN;
	else if (node->token == TOKEN_OUTPUT)
		new->token = FILE_OUT;
	else if (node->token == TOKEN_HEREDOC)
		new->token = WORD_LIM;
	if (new->token == WORD_LIM)
	{
		if (check_quote(new->content))
		{
			new->quote = 1;
			ptr = new->content;
			new->content = ft_quote(new->content);
			free(ptr);
		}
	}
}

void	ft_lstadd_back(t_list **lst, t_list *new, t_env *env)
{
	t_list	*node;

	node = *(lst);
	if (!new)
		return ;
	if (*(lst))
	{
		while (node->next)
			node = node->next;
		node->next = new;
		new->prev = node;
		if (node && new->token == TOKEN_WORD)
			ft_token_file(node, new, env);
	}
	else
	{
		if (new->token == TOKEN_WORD)
			ft_token_file(new, new, env);
		*(lst) = new;
	}
}

void	ft_lstadd_front(t_file **lst, t_file *new)
{
	t_file	*file;

	file = new;
	if (!new)
		return ;
	while (new->next)
		new = new->next;
	new->next = *lst;
	*lst = file;
}

t_file	*ft_filenew(t_list *list, t_env *env)
{
	t_file	*node;

	node = malloc(sizeof(t_file));
	if (!node || !list)
		return (NULL);
	node->fd = -2;
	node->token = list->token;
	node->name = NULL;
	if (list->content)
		node->name = ft_strdup(list->content);
	if (list->token == WORD_LIM)
		node->fd = ft_full_heredoc(list->content, env, list->quote);
	node->next = NULL;
	return (node);
}

void	ft_fileadd_back(t_file **lst, t_file *new)
{
	t_file	*node;

	node = *(lst);
	if (!new)
		return ;
	if (*(lst))
	{
		while (node->next)
			node = node->next;
		node->next = new;
	}
	else
		*(lst) = new;
}
