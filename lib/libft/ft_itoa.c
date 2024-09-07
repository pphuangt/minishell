/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/31 20:05:45 by pphuangt          #+#    #+#             */
/*   Updated: 2023/09/01 12:32:42 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_digit(int n)
{
	int	res;

	res = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		res++;
		n = n / 10;
	}
	return (res);
}

static void	write_itoa(char *res, int n, size_t digit_len)
{
	int	sign;

	sign = 1;
	if (n < 0)
	{
		*res = '-';
		sign = -1;
	}
	while (digit_len > (sign == -1))
	{
		res[digit_len - 1] = '0' + (n % 10 * (sign));
		n = n / 10;
		digit_len--;
	}
}

char	*ft_itoa(int n)
{
	size_t	digit_len;
	char	*res;

	digit_len = count_digit(n);
	if (n < 0)
		digit_len++;
	res = (char *)malloc(sizeof(char) * (digit_len + 1));
	if (!res)
		return (NULL);
	write_itoa(res, n, digit_len);
	res[digit_len] = '\0';
	return (res);
}
