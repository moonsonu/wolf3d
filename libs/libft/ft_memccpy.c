/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksonu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 16:23:19 by ksonu             #+#    #+#             */
/*   Updated: 2018/03/08 20:11:38 by ksonu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			a;

	d = (unsigned char *)dst;
	s = (unsigned char *)src;
	a = 0;
	while (a < n)
	{
		d[a] = s[a];
		if (d[a] == (unsigned char)c)
			return (dst + a + 1);
		a++;
	}
	return (NULL);
}
