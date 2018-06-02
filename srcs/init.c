/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksonu <ksonu@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 21:58:17 by ksonu             #+#    #+#             */
/*   Updated: 2018/06/01 22:31:13 by ksonu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	init_mlx(t_env *m)
{
	m->mlx_ptr = mlx_init();
	m->win_ptr = mlx_new_window(m->mlx_ptr, WINDOW, WINDOW, "WOLF3D - ksonu");
	m->image = mlx_new_image(m->mlx_ptr, WINDOW, WINDOW);
	m->data = (int*)mlx_get_data_addr(m->image, &m->bbp, &m->size, &m->endian);
}

void	init_env(t_env *m)
{
	int		i;
	m->ray.posX = 22;
	m->ray.posY = 12;
	m->ray.dirX = -1;
	m->ray.dirY = 0;
	m->ray.planeX = 0;
	m->ray.planeY = 0.66;
	i = -1;
	while (++i < 8)
		m->texture[i] = malloc(sizeof(int) * 64);
}

void	init_texture(t_env *m)
{
	int		x;
	int		y;

	x = -1;
	while (++x < TEXTWD)
	{
		y = -1;
		while (++y < TEXTHT)
		{
			m->xorcolor = (x * 256 / TEXTHT) ^ (y * 256 / TEXTHT);
			m->ycolor = y * 256 / TEXTHT;
			m->xycolor = y * 128 / TEXTHT + x * 128 / TEXTWD;
			m->texture[0][TEXTWD * y + x] = (m->xorcolor + 256 * m->xorcolor + 65536 * m->xorcolor);
			m->texture[1][TEXTWD * y + x] = (256 * m->xorcolor);
			m->texture[2][TEXTWD * y + x] = (m->xorcolor + 128 * m->xorcolor + 32768 * m->xorcolor);
			m->texture[3][TEXTWD * y + x] = (65536 * m->xorcolor);
			m->texture[4][TEXTWD * y + x] = (m->xorcolor + 64 * m->xorcolor + 16384 * m->xorcolor);
			m->texture[5][TEXTWD * y + x] = (m->xorcolor + 64 * m->xorcolor + 65536 * m->xorcolor);
			m->texture[6][TEXTWD * y + x] = 65536 * m->ycolor;
			m->texture[7][TEXTWD * y + x] = 128 + 256 * 128 + 65536 * 128;
		}
	}
}
