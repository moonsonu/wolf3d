/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksonu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/28 22:50:25 by ksonu             #+#    #+#             */
/*   Updated: 2018/03/10 17:48:33 by ksonu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_itoa(int n)
{
	char	*rc;
	int		len;
	int		c;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	c = n;
	len = ft_itoa_len(n);
	if (!(rc = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	rc[len] = '\0';
	if (n < 0)
		n *= -1;
	while (len--)
	{
		rc[len] = n % 10 + '0';
		n /= 10;
	}
	if (c < 0)
		rc[0] = '-';
	return (rc);
}
