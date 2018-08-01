/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksonu <ksonu@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/31 15:52:28 by ksonu             #+#    #+#             */
/*   Updated: 2018/07/31 18:29:40 by ksonu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	plot_mm(t_env *m, int x, int s, int e)
{
	while (s < e)
	{
		m->data[x + (s * m->size) / 4] = m->color;
		s++;
	}
}

void	plot_square(t_env *m, int x, int y)
{
	int px;
	int py;

	px = x * 3;
	py = y * 3;
	while (px++ < (x * 3) + 3)
	{
		plot_mm(m, px, py, py + 3);
	}
}

void	plot_dot(t_env *m)
{
	int i;

	i = -1;
	while (++i <= 3)
	{
		m->color = 0xFD67DF;
		plot_mm(m, ((m->ray.posx + 160) * 3) + i, ((m->ray.posy + 20)
			* 3), ((m->ray.posy + 20) * 3) + 3);
	}
}

void	minimap(t_env *m)
{
	int x;
	int y;

	y = -1;
	while (++y < m->map_maxy)
	{
		x = -1;
		while (++x < m->map_maxx)
		{
			if (m->map[y][x].type == 1)
			{
				m->color = 0x88A0A1;
				plot_square(m, x + 160, y + 20);
			}
			else if (m->map[y][x].type > 1)
			{
				m->color = 0xC7D6D8;
				plot_square(m, x + 160, y + 20);
			}
		}
	}
	plot_dot(m);
}
