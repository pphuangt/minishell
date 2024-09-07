/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pphuangt <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 18:55:15 by pphuangt          #+#    #+#             */
/*   Updated: 2023/12/10 11:01:01 by pphuangt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_overflow(long long res, int sign, char c)
{
	if (res * sign > (LLONG_MAX - (c - '0')) / 10 && sign == 1)
		return (-1);
	if (res * sign < (LLONG_MIN + (c - '0')) / 10 && sign == -1)
		return (0);
	return (1);
}

static long long	cal_res(const char *str, size_t i, int sign)
{
	long long	res;
	int			overflow;

	res = 0;
	while (ft_isdigit(str[i]))
	{
		overflow = is_overflow(res, sign, str[i]);
		if (overflow != 1)
			return (overflow);
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return (sign * res);
}

int	ft_atoi(const char *str)
{
	int			sign;
	long long	res;
	size_t		i;

	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r')
		i++;
	sign = 1;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	res = cal_res(str, i, sign);
	return ((int)res);
}
