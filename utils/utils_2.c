/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: raitmous <raitmous@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/25 01:36:17 by raitmous          #+#    #+#             */
/*   Updated: 2023/06/25 02:31:35 by raitmous         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_token(char c)
{
	if (c == '|' || c == '<' || c == '>' || c == '&' || c == ' ' || c == '\t'
		|| c == '(' || c == ')')
	{
		return (1);
	}
	return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
	{
		return (1);
	}
	return (0);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
	{
		return (1);
	}
	return (0);
}

int	ft_nbrlen(long n)
{
	int	count;

	count = 0;
	if (n <= 0)
	{
		count++;
		n *= (-1);
	}
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	long	r;
	char	*str;
	int		len;
	int		sign;

	r = n;
	sign = 0;
	len = ft_nbrlen(r);
	str = malloc(len + 1);
	if (!str)
		return (0);
	str[len] = 0;
	if (r < 0)
	{
		str[0] = '-';
		r *= (-1);
		len--;
		sign++;
	}
	while (len > 0)
	{
		str[len-- + sign - 1] = r % 10 + 48;
		r /= 10;
	}
	return (str);
}
