/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raitmous <raitmous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 00:46:41 by raitmous          #+#    #+#             */
/*   Updated: 2023/06/25 03:22:44 by raitmous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_insetdata(t_data *data, t_data *new)
{
	new->arg = data->arg;
	new->files = data->files;
	new->token = data->token;
}

void	buildtree_sub1(t_data **data, int *par, t_data **node)
{
	while ((*data))
	{
		if ((*data)->arg && !ft_strcmp((*data)->arg[0], "("))
			(*par)++;
		else if ((*data)->arg && !ft_strcmp((*data)->arg[0], ")"))
			(*par)--;
		if (!(*par))
			break ;
		if (((*data)->arg && ft_strcmp((*data)->arg[0], "(")) || (*par) > 1)
			ft_dtadd_back(&(*node), ft_datanew((*data)->arg, (*data)->files,
					(*data)->token));
		(*data) = (*data)->right;
	}
}

void	buildtree_sub2(t_data **data, t_data **current, t_data **root,
		t_data **node)
{
	if (!(*root))
	{
		(*root) = ft_dtnew(buildtree(NULL, NULL, (*node)), NULL);
		ft_freedata(*node, 0);
		ft_insetdata((*data), (*root));
		(*root)->in_par = 1;
	}
	else
	{
		(*current)->right = ft_dtnew(buildtree(NULL, NULL, (*node)), NULL);
		ft_freedata(*node, 0);
		ft_insetdata((*data), (*current)->right);
	}
	if ((*data)->right && !(*data)->right->arg && (*data)->right->files)
	{
		if ((*root)->in_par)
			ft_lstadd_front(&(*root)->files, (*data)->right->files);
		else
			ft_lstadd_front(&(*current)->right->files, (*data)->right->files);
		(*data) = (*data)->right;
	}
}

void	buildtree_sub3(t_data **data, t_data **current, t_data **root)
{
	if (((*root)->token != TOKEN_AND && (*root)->token != TOKEN_OR)
		|| (*root)->in_par)
	{
		(*root) = ft_dtnew((*root), NULL);
		(*current) = (*root);
	}
	else
	{
		if ((*current)->token == TOKEN_PIPE)
		{
			(*current)->left = ft_dtnew((*current)->left, (*current)->right);
			ft_insetdata((*data), (*current)->left);
		}
		else
		{
			(*current)->right = ft_dtnew((*current)->right, NULL);
			(*current) = (*current)->right;
		}
	}
	ft_insetdata((*data), (*current));
}

t_data	*buildtree(t_data *root, t_data *current, t_data *data)
{
	t_data	*node;
	int		par;

	par = 0;
	node = NULL;
	if (!data)
		return (root);
	if (data->token == TOKEN_PAR)
		(buildtree_sub1(&data, &par, &node),
			buildtree_sub2(&data, &current, &root, &node));
	else if (!root || data->token == TOKEN_AND || data->token == TOKEN_OR)
	{
		root = ft_dtnew(root, NULL);
		current = root;
		ft_insetdata(data, current);
	}
	else if (data->token == TOKEN_PIPE)
		buildtree_sub3(&data, &current, &root);
	else
	{
		current->right = ft_dtnew(NULL, NULL);
		ft_insetdata(data, current->right);
	}
	return (buildtree(root, current, data->right));
}
