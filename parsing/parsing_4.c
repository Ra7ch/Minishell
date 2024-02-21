/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raitmous <raitmous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 00:47:21 by raitmous          #+#    #+#             */
/*   Updated: 2023/06/25 03:24:12 by raitmous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_full_data_sub1(t_list **list, char **str, t_file **files,
		t_data **data)
{
	if (!(*list)->next || (*list)->token == TOKEN_PIPE
		|| (*list)->token == TOKEN_AND || (*list)->token == TOKEN_OR
		|| (*list)->token == TOKEN_PAR)
	{
		if ((*str) || (*files))
			ft_dtadd_back(&(*data), ft_datanew(ft_split((*str), 3), (*files),
					TOKEN_WORD));
		if ((*list)->token < 3 || (*list)->token == TOKEN_PAR)
			ft_dtadd_back(&(*data), ft_datanew(ft_split((*list)->content, 3),
					NULL, (*list)->token));
		(*files) = NULL;
		free((*str));
		(*str) = NULL;
	}
	(*list) = (*list)->next;
}

void	ft_full_data_sub2(t_list **list, char **str, t_file **files, t_env *env)
{
	if ((*list)->token == TOKEN_WORD)
		*str = ft_strjoin(ft_strjoin(*str, (char []){3, 0}), (*list)->content);
	else if ((*list)->token == FILE_OUT || (*list)->token == FILE_APP)
		ft_fileadd_back(files, ft_filenew((*list), env));
}

t_data	*ft_full_data(t_list *list, t_env *env)
{
	t_file	*files;
	t_data	*data;
	char	*str;

	str = NULL;
	data = NULL;
	files = NULL;
	while (list)
	{
		if (ft_check_error(list))
			return (free(str), ft_freedata(data, 1), ft_freefile(files), NULL);
		if (list->token == FILE_IN || list->token == WORD_LIM)
		{
			ft_fileadd_back(&files, ft_filenew(list, env));
			if (g_v.heredoc == 1)
				return (free(str), ft_freedata(data, 1), ft_freefile(files),
					NULL);
		}
		else if (list->token == TOKEN_WORD || list->token == FILE_OUT
			|| list->token == FILE_APP)
			ft_full_data_sub2(&list, &str, &files, env);
		ft_full_data_sub1(&list, &str, &files, &data);
	}
	return (data);
}
