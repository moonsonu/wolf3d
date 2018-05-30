/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksonu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/19 20:49:24 by ksonu             #+#    #+#             */
/*   Updated: 2018/03/10 17:45:05 by ksonu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*rc;
	int		i;
	int		l;

	i = 0;
	l = ft_strlen(s1);
	rc = (char*)malloc(sizeof(char) * (l + 1));
	if (!rc)
		return (NULL);
	while (i < l)
	{
		rc[i] = s1[i];
		i++;
	}
	rc[i] = '\0';
	return (rc);
}
