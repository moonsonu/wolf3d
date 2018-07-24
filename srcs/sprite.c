/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksonu <ksonu@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 21:03:33 by ksonu             #+#    #+#             */
/*   Updated: 2018/07/23 21:22:10 by ksonu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ray_sprite(t_env *m)
{
	int		i;

	i = -1;
	while (++i < m->numsprite)
	{
		m->spriteX = sprite[spriteorder[i]].x - m->ray.posX;
		m->spriteY = sprite[spriteorder[i]].y - m->ray.posY;
	}
}
