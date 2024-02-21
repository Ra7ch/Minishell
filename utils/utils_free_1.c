/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-zeh <mben-zeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:55:11 by mben-zeh          #+#    #+#             */
/*   Updated: 2023/06/25 03:32:27 by mben-zeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_free(t_list *list, t_data *data, t_data *root, t_file *file)
{
	(void)file;
	if (list)
		ft_freelist(list);
	if (data)
		ft_freedata(data, 1);
	if (root)
		ft_freeroot(root);
}

void	ft_free_word(t_word *word)
{
	t_word	*node;

	node = NULL;
	while (word)
	{
		node = word->next;
		free(word);
		word = node;
	}
}

void	ft_freelist(t_list *lst)
{
	t_list	*node;

	if (!lst)
		return ;
	while (lst)
	{
		node = lst->next;
		if (lst->content)
			free(lst->content);
		free(lst);
		lst = node;
	}
}

void	ft_freeroot(t_data *root)
{
	if (!root)
		return ;
	if ((root->left && root->right) || root->token == TOKEN_PAR)
	{
		ft_freeroot(root->left);
		ft_freeroot(root->right);
	}
	free(root);
}

void	ft_freefile(t_file *file)
{
	t_file	*node;

	while (file)
	{
		node = file->next;
		free(file->name);
		free(file);
		file = node;
	}
}
