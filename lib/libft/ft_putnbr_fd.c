/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/04 14:54:53 by pphuangt          #+#    #+#             */
/*   Updated: 2023/09/05 20:00:04 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_divide(int n)
{
	int	res;

	res = 1;
	while (n >= 10)
	{
		res = res * 10;
		n = n / 10;
	}
	return (res);
}

static void	print_fd(int n, int divide, int fd)
{
	int	c;

	while (divide != 0)
	{
		c = n / divide + '0';
		write(fd, &c, 1);
		n = n % divide;
		divide = divide / 10;
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	char	c;
	int		sign;
	int		last_digit;
	int		divide;

	sign = 1;
	if (n < 0)
	{
		write(fd, "-", 1);
		sign = -1;
	}
	last_digit = n % 10 * sign;
	n = n / 10 * sign;
	if (n != 0)
	{
		divide = count_divide(n);
		print_fd(n, divide, fd);
	}
	c = last_digit + '0';
	write(fd, &c, 1);
}
