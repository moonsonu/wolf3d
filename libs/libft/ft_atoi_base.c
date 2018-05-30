/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksonu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/28 19:40:34 by ksonu             #+#    #+#             */
/*   Updated: 2018/05/29 15:03:32 by ksonu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long		ft_convert(const char *str, int base)
{
	int		i;
	long	n;

	i = 0;
	n = 0;
	while ((str[i] >= '0' && str[i] <= '9') || (str[i] >= 'a' && str[i] <= 'f')
			|| (str[i] >= 'A' && str[i] <= 'F'))
	{
		n *= base;
		if (str[i] >= '0' && str[i] <= '9')
			n += str[i] - 48;
		else if (str[i] >= 'a' && str[i] <= 'f')
			n += str[i] - 87;
		else if (str[i] >= 'A' && str[i] <= 'F')
			n += str[i] - 55;
		i++;
	}
	return (n);
}

int				ft_atoi_base(const char *str, int base)
{
	int		i;
	int		sign;
	long	num;

	i = 0;
	sign = 1;
	i = ft_whtspace(str, i);
	if (str[i] == '-')
	{
		if (str[i + 1] == '-' || str[i + 1] == '+')
			return (0);
		i++;
		sign = -1;
	}
	if (str[i] == '+')
		i++;
	num = ft_convert(str + i, base);
	return (sign * (int)num);
}
