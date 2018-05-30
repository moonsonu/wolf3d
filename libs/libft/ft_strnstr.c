/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksonu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/22 23:21:20 by ksonu             #+#    #+#             */
/*   Updated: 2018/03/10 17:46:18 by ksonu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned int		i;
	unsigned int		j;
	size_t				l;

	i = 0;
	l = ft_strlen(needle);
	if (l == 0)
		return ((char *)haystack);
	while (haystack[i] != '\0' && len >= (l + i))
	{
		j = 0;
		while (needle[j] == haystack[i + j])
		{
			if (j == (l - 1))
				return ((char *)haystack + i);
			j++;
		}
		i++;
	}
	return (0);
}
