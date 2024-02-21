/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raitmous <raitmous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 01:36:17 by raitmous          #+#    #+#             */
/*   Updated: 2023/06/25 02:31:43 by raitmous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_data	*ft_dtnew(t_data *left, t_data *right)
{
	t_data	*node;

	node = malloc(sizeof(t_data));
	if (!node)
		return (NULL);
	node->arg = NULL;
	node->files = NULL;
	node->fdin = -2;
	node->fdout = -2;
	node->left = left;
	node->right = right;
	node->in_par = 0;
	return (node);
}

t_data	*ft_datanew(char **arg, t_file *files, t_TokenType token)
{
	t_data	*node;

	node = malloc(sizeof(t_data));
	if (!node)
		return (NULL);
	node->token = token;
	node->arg = arg;
	node->files = files;
	node->left = NULL;
	node->right = NULL;
	node->in_par = 0;
	return (node);
}

void	ft_dtadd_back(t_data **lst, t_data *new)
{
	t_data	*node;

	node = *(lst);
	if (!new)
		return ;
	if (*(lst))
	{
		while (node->right)
			node = node->right;
		new->left = node;
		node->right = new;
	}
	else
		*(lst) = new;
}

t_env	*ft_envnew(char *var, char *value)
{
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (NULL);
	node->value = value;
	node->var = var;
	node->next = NULL;
	return (node);
}

void	ft_envadd_back(t_env **lst, t_env *new)
{
	t_env	*node;

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
