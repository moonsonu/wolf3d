/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksonu <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/06 15:53:16 by ksonu             #+#    #+#             */
/*   Updated: 2018/03/10 17:49:24 by ksonu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_lstdel(t_list **alst, void (*del)(void *, size_t))
{
	t_list		*nxtlst;
	t_list		*tmp;

	if (alst != NULL)
	{
		nxtlst = *alst;
		while (nxtlst != NULL)
		{
			del(nxtlst->content, nxtlst->content_size);
			tmp = nxtlst->next;
			free(nxtlst);
			nxtlst = tmp;
		}
		*alst = NULL;
	}
}
