/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_counter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksonu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 21:30:33 by ksonu             #+#    #+#             */
/*   Updated: 2018/03/07 14:33:35 by ksonu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_counter(char const *str, char c)
{
	int		i;
	int		word;

	i = 0;
	word = 0;
	while (str[i] != '\0')
	{
		while (str[i] != c)
		{
			if (str[i] != '\0')
				i++;
			else
				break ;
		}
		while (str[i] == c)
			i++;
		word++;
	}
	return (word);
}
