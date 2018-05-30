/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksonu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/23 01:02:08 by ksonu             #+#    #+#             */
/*   Updated: 2018/03/10 17:46:50 by ksonu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		*ft_memalloc(size_t size)
{
	void	*str;

	str = (void *)malloc(sizeof(void) * size);
	if (str == '\0')
		return (NULL);
	ft_memset(str, 0, size);
	return (str);
}
