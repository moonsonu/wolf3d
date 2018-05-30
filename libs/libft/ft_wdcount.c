/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wdcount.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksonu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/18 18:04:16 by ksonu             #+#    #+#             */
/*   Updated: 2018/04/18 19:33:46 by ksonu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_wdcount(char *str, char c)
{
	int		result;
	int		i;
	int		word;

	i = 0;
	result = 0;
	while (str[i])
	{
		if (str[i] && str[i] == c)
			word = 0;
		else if (str[i] != c && word == 0)
		{
			word = 1;
			result++;
		}
		i++;
	}
	return (result);
}
