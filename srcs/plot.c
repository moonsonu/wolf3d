/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksonu <ksonu@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 16:39:24 by ksonu             #+#    #+#             */
/*   Updated: 2018/06/05 16:56:30 by ksonu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	plot_floor(t_env *m, int x)
{
	int		y;

	m->ray.distwall = m->ray.perpwalldist;
	m->ray.distpos = 0.0;
	if (m->ray.end < 0)
		m->ray.end = WINDOW;
	y = m->ray.end;
	while (++y < WINDOW)
	{
		m->ray.distcurr = WINDOW / (2.0 * y - WINDOW);
		m->ray.weight = (m->ray.distcurr - m->ray.distpos) / (m->ray.distwall -
				m->ray.distpos);
		m->ray.currfloorX = m->ray.weight * m->ray.floorX +
			(1.0 - m->ray.weight) * m->ray.posX;
		m->ray.currfloorY = m->ray.weight * m->ray.floorY +
			(1.0 - m->ray.weight) * m->ray.posY;
		m->ray.floortextX = (int)(m->ray.currfloorX * TEXTWD) % (int)TEXTWD;
		m->ray.floortextY = (int)(m->ray.currfloorY * TEXTHT) % (int)TEXTHT;
		m->data[y * (int)WINDOW + x] = ((m->texture[2][(int)(TEXTHT *
						m->ray.floortextY + m->ray.floortextX)]) >> 1)
			& 8355711;
		m->data[(int)(WINDOW - y) * WINDOW + x] = m->texture[3][(int)(TEXTHT
				* m->ray.floortextY + m->ray.floortextX)];
	}
}

void	plot_wall(t_env *m, int x)
{
	int		y;

	m->ray.texX = (int)(m->ray.wallX * TEXTWD);
	if (m->ray.side == 0 && m->ray.raydirX > 0)
		m->ray.texX = TEXTWD - m->ray.texX - 1;
	if (m->ray.side == 1 && m->ray.raydirY < 0)
		m->ray.texX = TEXTWD - m->ray.texX - 1;
	y = m->ray.start - 1;
	while (++y < m->ray.end)
	{
		m->ray.d = y * 256 - WINDOW * 128 + m->ray.lineheight * 128;
		m->ray.texY = ((m->ray.d * TEXTHT) / m->ray.lineheight) / 256;
		m->ray.color = m->texture[0][(int)(TEXTWD * m->ray.texY +
				m->ray.texX)];
		if (m->ray.side == 1)
			m->ray.color = (m->ray.color >> 1) & 8355711;
		m->data[y * ((int)WINDOW) + x] = m->ray.color;
	}
}
