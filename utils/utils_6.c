/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raitmous <raitmous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 01:38:59 by raitmous          #+#    #+#             */
/*   Updated: 2023/06/25 02:31:45 by raitmous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_fork	*ft_forknew(pid_t pid, int fdin, int fdout)
{
	t_fork	*node;

	node = malloc(sizeof(t_fork));
	if (!node)
		return (NULL);
	node->pid = pid;
	node->fdin = fdin;
	node->fdout = fdout;
	node->next = NULL;
	return (node);
}

void	ft_forkadd_back(t_fork **lst, t_fork *new)
{
	t_fork	*node;

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

t_pipe	*ft_fdnew(int *fd)
{
	t_pipe	*node;

	node = malloc(sizeof(t_pipe));
	if (!node)
		return (NULL);
	node->fd = fd;
	node->next = NULL;
	node->prev = NULL;
	node->fdin = -2;
	node->fdout = -2;
	return (node);
}

void	ft_fdadd_front(t_pipe **lst, t_pipe *new)
{
	t_pipe	*node;

	node = new;
	if (!new)
		return ;
	while (new->next)
		new = new->next;
	if (*lst)
	{
		new->next = *lst;
		(*lst)->prev = new;
	}
	*lst = node;
}

void	ft_fdadd_back(t_pipe **lst, t_pipe *new)
{
	t_pipe	*node;

	node = *(lst);
	if (!new)
		return ;
	if (*(lst))
	{
		while (node->next)
			node = node->next;
		new->prev = node;
		node->next = new;
	}
	else
		*(lst) = new;
}
