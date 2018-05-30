/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksonu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/26 17:35:26 by ksonu             #+#    #+#             */
/*   Updated: 2018/03/10 17:48:24 by ksonu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char				**ft_strsplit(char const *s, char c)
{
	char	**rc;
	int		index;
	int		a;

	if (!s)
		return (NULL);
	a = ft_counter(s, c);
	rc = (char **)malloc(sizeof(char *) * (a + 1));
	if (!rc)
		return (NULL);
	index = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			rc[index] = ft_string(s, c);
			index++;
			while (*s && *s != c)
				s++;
		}
	}
	rc[index] = 0;
	return (rc);
}
