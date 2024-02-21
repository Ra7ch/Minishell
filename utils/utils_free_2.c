/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_free_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-zeh <mben-zeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:55:11 by mben-zeh          #+#    #+#             */
/*   Updated: 2023/06/25 03:32:34 by mben-zeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_freedata(t_data *lst, int all)
{
	t_data	*node;
	int		i;

	i = 0;
	node = NULL;
	if (!lst)
		return ;
	while (lst)
	{
		node = lst->right;
		if (all)
		{
			if (lst->arg)
			{
				ft_free_arg(lst->arg);
				lst->arg = NULL;
			}
			if (lst->files)
				ft_freefile(lst->files);
		}
		free(lst);
		lst = node;
	}
}

void	ft_free_arg(char **arg)
{
	int	i;

	i = 0;
	if (arg)
	{
		while (arg && arg[i])
			i++;
		while (i)
			free(arg[--i]);
		free(arg);
		arg = NULL;
	}
}
