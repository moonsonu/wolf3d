/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksonu <ksonu@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 21:58:17 by ksonu             #+#    #+#             */
/*   Updated: 2018/06/05 17:18:22 by ksonu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	init_mlx(t_env *m)
{
	m->image = mlx_new_image(m->mlx_ptr, WINDOW, WINDOW);
	m->data = (int*)mlx_get_data_addr(m->image, &m->bbp, &m->size, &m->endian);
}

void	init_env(t_env *m)
{
	int		i;

	m->ray.posX = 10;
	m->ray.posY = 10;
	m->ray.dirX = -1;
	m->ray.dirY = 0;
	m->ray.planeX = 0;
	m->ray.planeY = 0.66;
	i = -1;
	while (++i < 4)
		m->texture[i] = malloc(4 * (TEXTHT * TEXTWD));
}

void	init_texture(t_env *m)
{
	int		x;
	int		y;

	y = -1;
	while (++y < TEXTHT)
	{
		x = -1;
		while (++x < TEXTWD)
		{
			m->texture[0][TEXTWD * y + x] = 0xFFFFFF;
			m->texture[1][TEXTWD * y + x] = 0x32FDE5;
			m->texture[2][TEXTWD * y + x] = 0x800000;
			m->texture[3][TEXTWD * y + x] = 0xABC335;
		}
	}
}
