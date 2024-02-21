/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raitmous <raitmous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 01:36:17 by raitmous          #+#    #+#             */
/*   Updated: 2023/06/25 02:31:37 by raitmous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_atoi(char *str)
{
	int	i;
	int	sign;
	int	n;

	n = 0;
	i = 0;
	sign = 1;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n *= 10;
		n += str[i] - '0';
		i++;
	}
	return (n * sign);
}

char	*ft_check(char *s1, char *s2)
{
	char	*str;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1)
		return (ft_strdup(s2));
	else
	{
		str = ft_strdup(s1);
		free(s1);
		return (str);
	}
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*str;
	int		i;

	i = 0;
	if (!s1 || !s2)
		return (ft_check(s1, s2));
	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!str)
		return (0);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	while (*s2)
	{
		str[i] = *s2;
		s2++;
		i++;
	}
	str[i] = 0;
	free(s1);
	s1 = NULL;
	return (str);
}

void	ft_token_redirect(t_list *node, char *content)
{
	if (!ft_strcmp(content, ">>"))
		node->token = TOKEN_APPEND;
	else if (!ft_strcmp(content, "<<"))
		node->token = TOKEN_HEREDOC;
	else if (!ft_strcmp(content, "|"))
		node->token = TOKEN_PIPE;
	else if (!ft_strcmp(content, "&&"))
		node->token = TOKEN_AND;
	else if (!ft_strcmp(content, "||"))
		node->token = TOKEN_OR;
	else if (!ft_strcmp(content, "<"))
		node->token = TOKEN_INPUT;
	else if (!ft_strcmp(content, ">"))
		node->token = TOKEN_OUTPUT;
	else if (!ft_strcmp(content, "(") || !ft_strcmp(content, ")"))
		node->token = TOKEN_PAR;
	else
		node->token = TOKEN_WORD;
}

t_list	*ft_lstnew(char *content)
{
	t_list	*node;

	if (!content)
		return (NULL);
	node = malloc(sizeof(t_list));
	if (!node)
		return (NULL);
	ft_token_redirect(node, content);
	node->content = content;
	node->quote = 0;
	node->next = NULL;
	node->prev = NULL;
	return (node);
}
