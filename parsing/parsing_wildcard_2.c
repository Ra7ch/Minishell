/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_wildcard_2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raitmous <raitmous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 01:09:55 by raitmous          #+#    #+#             */
/*   Updated: 2023/06/25 03:34:52 by raitmous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_pattern(t_word *p, const char *line)
{
	if (p == NULL && *line == '\0')
		return (1);
	if (p == NULL || *line == '\0')
		return (0);
	if (p->c == '*' && p->next == NULL)
		return (1);
	if (p->c == '*' && p->type == STATE_NORMAL)
	{
		return (check_pattern(p->next, line) || check_pattern(p, line + 1));
	}
	if (p->c == *line || p->c == '?')
	{
		return (check_pattern(p->next, line + 1));
	}
	return (0);
}

void	expand_wildcard_sub_sub(int j, char **ptr, struct dirent *entry)
{
	char	*name;
	char	*tmp;
	int		i;

	name = NULL;
	i = -1;
	name = ft_strdup(entry->d_name);
	while (name[++i])
		if (name[i] == '\"' || name[i] == '\'')
			name[i] -= 29;
	if (name[0] != '.')
	{
		if (j == 1)
		{
			tmp = name;
			name = ft_strjoin(ft_strdup("./"), name);
			free(tmp);
		}
		(*ptr) = ft_strjoin(ft_strjoin((*ptr), (char []){3, 0}),
				name);
	}
	free(name);
}

void	expand_wildcard_sub(int j, t_word *p, char **ptr, char *str)
{
	DIR				*dir;
	struct dirent	*entry;

	if (check_wildcard(str))
	{
		dir = opendir(".");
		entry = readdir(dir);
		while (entry != NULL)
		{
			if (entry == NULL)
				break ;
			if (check_pattern(p, entry->d_name))
				expand_wildcard_sub_sub(j, ptr, entry);
			entry = readdir(dir);
		}
		closedir(dir);
	}
}

char	*expand_wildcard(char *str)
{
	int		i;
	char	*ptr;
	t_word	*p;
	t_word	*tmp;
	int		j;

	j = 0;
	p = NULL;
	ptr = NULL;
	i = -1;
	str = ft_strdup(str);
	while (str && str[++i])
		if (str[i] == 5 || str[i] == 10)
			str[i] += 29;
	p = token_words(str);
	tmp = p;
	if (p && p->c == '.' && p->next && p->next->c == '/')
	{
		p = p->next->next;
		j = 1;
	}
	return (expand_wildcard_sub(j, p, &ptr, str), ft_free_word(tmp), free(str),
		ptr);
}
