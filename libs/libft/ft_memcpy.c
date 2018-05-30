/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksonu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 15:39:57 by ksonu             #+#    #+#             */
/*   Updated: 2018/03/10 17:44:25 by ksonu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			a;

	a = 0;
	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	while (a < n)
	{
		d[a] = s[a];
		a++;
	}
	return (dst);
}
