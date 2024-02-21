/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mben-zeh <mben-zeh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:38:38 by mben-zeh          #+#    #+#             */
/*   Updated: 2023/06/25 05:03:37 by mben-zeh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_split_join(char *ptr, t_env *env)
{
	t_list	*list;
	t_list	*node;
	char	*str;

	list = NULL;
	str = NULL;
	node = NULL;
	if (!ptr)
		return (NULL);
	ft_spl(ptr, &list, env);
	node = list;
	while (list)
	{
		if (!str)
			str = ft_strjoin(str, list->content);
		else
			str = ft_strjoin(ft_strjoin(str, (char []){3, 0}), list->content);
		list = list->next;
	}
	ft_freelist(node);
	free(ptr);
	return (str);
}

void	ft_print_ambiguous(t_data *root)
{
	ft_putstr(root->files->name, 2);
	ft_putstr(":", 2);
	ft_putstr(" ambiguous redirect\n", 2);
	if (root->fdin > 2)
		close(root->fdin);
	root->fdin = -1;
	if (root->fdout > 2)
		close(root->fdout);
	root->fdout = -1;
}

int	ft_openfile_sub1(t_data **root, t_env *env, char ***arg, char *ptr)
{
	if (ptr && (*root)->files->token != WORD_LIM)
	{
		*arg = ft_args((char *[]){ptr, NULL}, env);
		if (!(*arg) || (*arg)[1])
		{
			ft_print_ambiguous(*root);
			ft_free_arg(*arg);
			return (1);
		}
	}
	return (0);
}

void	ft_openfile_sub2(t_data **root, char **arg)
{
	if ((*root)->files->token == FILE_IN || (*root)->files->token == WORD_LIM)
	{
		if ((*root)->fdin != -2)
			close((*root)->fdin);
		if ((*root)->files->token == FILE_IN)
			(*root)->fdin = open(arg[0], O_RDONLY);
		else
			(*root)->fdin = (*root)->files->fd;
	}
	else
	{
		if ((*root)->fdout > 2)
			close((*root)->fdout);
		if ((*root)->files->token == FILE_APP)
			(*root)->fdout = open(arg[0], O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			(*root)->fdout = open(arg[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	}
}

void	ft_openfile(t_data *root, t_env *env)
{
	char	*ptr;
	char	**arg;

	arg = NULL;
	while (root->files)
	{
		ptr = root->files->name;
		if (ft_openfile_sub1(&root, env, &arg, ptr))
			return ;
		ft_openfile_sub2(&root, arg);
		if (root->fdin == -1 || root->fdout == -1)
		{
			if (arg && !arg[0])
				ft_putstr(" : No such file or directory\n", 2);
			else
				perror(arg[0]);
			ft_free_arg(arg);
			return ;
		}
		if (root->files->token != WORD_LIM)
			ft_free_arg(arg);
		root->files = root->files->next;
	}
}
