/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raitmous <raitmous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/04 18:40:51 by mben-zeh          #+#    #+#             */
/*   Updated: 2023/06/25 02:31:32 by raitmous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

void	ft_putstr(char *s, int fd)
{
	if (!s || fd < 0)
		return ;
	write(fd, s, ft_strlen(s));
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] == s2[i] && s1[i] && s2[i])
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char	*ft_strdup(const char *s1)
{
	int		len;
	int		i;
	char	*str;

	if (!s1)
		return (NULL);
	len = ft_strlen(s1);
	i = 0;
	str = malloc(len + 1);
	if (!str)
		return (0);
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	size_t	slen;

	i = 0;
	str = NULL;
	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (slen - 1 < start || slen == 0)
		return (NULL);
	if (slen - (size_t)start < len)
		len = slen - (size_t)start;
	str = malloc(len + 1);
	if (!str)
		return (0);
	while ((s + start)[i] && i < len)
	{
		str[i] = (s + start)[i];
		i++;
	}
	str[i] = 0;
	return (str);
}
