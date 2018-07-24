/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksonu <ksonu@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 22:00:08 by ksonu             #+#    #+#             */
/*   Updated: 2018/07/23 21:22:12 by ksonu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ray_prep(t_env *m, int x)
{
	m->ray.cameraX = 2 * x / (double)WINDOW - 1;
	m->ray.raydirX = m->ray.dirX + m->ray.planeX * m->ray.cameraX;
	m->ray.raydirY = m->ray.dirY + m->ray.planeY * m->ray.cameraX;
	m->ray.mapX = (int)m->ray.posX;
	m->ray.mapY = (int)m->ray.posY;
	m->ray.deltadistX = fabs(1 / m->ray.raydirX);
	m->ray.deltadistY = fabs(1 / m->ray.raydirY);
	m->ray.hit = 0;
	m->ray.stepX = (m->ray.raydirX < 0) ? -1 : 1;
	(m->ray.raydirX < 0) ? (m->ray.sidedistX = (m->ray.posX - m->ray.mapX) *
			m->ray.deltadistX) : (m->ray.sidedistX = (m->ray.mapX + 1.0 -
					m->ray.posX) * m->ray.deltadistX);
	m->ray.stepY = (m->ray.raydirY < 0) ? -1 : 1;
	(m->ray.raydirY < 0) ? (m->ray.sidedistY = (m->ray.posY - m->ray.mapY) *
			m->ray.deltadistY) : (m->ray.sidedistY = (m->ray.mapY + 1.0 -
					m->ray.posY) * m->ray.deltadistY);
}

void	ray_dda(t_env *m)
{
	while (m->ray.hit == 0)
	{
		if (m->ray.sidedistX < m->ray.sidedistY)
		{
			m->ray.sidedistX += m->ray.deltadistX;
			m->ray.mapX += m->ray.stepX;
			m->ray.side = 0;
		}
		else
		{
			m->ray.sidedistY += m->ray.deltadistY;
			m->ray.mapY += m->ray.stepY;
			m->ray.side = 1;
		}
		if (m->map[m->ray.mapY][m->ray.mapX].type > 0)
		{
			m->ray.hit = 1;
			m->ray.textnum = m->map[m->ray.mapY][m->ray.mapX].type;
		}
	}
}

void	ray_wall(t_env *m)
{
	if (m->ray.side == 0)
		m->ray.perpwalldist = (m->ray.mapX - m->ray.posX +
				(1 - m->ray.stepX) / 2) / m->ray.raydirX;
	else
		m->ray.perpwalldist = (m->ray.mapY - m->ray.posY +
				(1 - m->ray.stepY) / 2) / m->ray.raydirY;
	m->ray.lineheight = (int)(WINDOW / m->ray.perpwalldist);
	m->ray.start = -(m->ray.lineheight) / 2 + WINDOW / 2;
	if (m->ray.start < 0)
		m->ray.start = 0;
	m->ray.end = m->ray.lineheight / 2 + WINDOW / 2;
	if (m->ray.end >= WINDOW)
		m->ray.end = WINDOW - 1;
	if (m->ray.side == 0)
		m->ray.wallX = m->ray.posY + m->ray.perpwalldist * m->ray.raydirY;
	else
		m->ray.wallX = m->ray.posX + m->ray.perpwalldist * m->ray.raydirX;
	m->ray.wallX -= floor((m->ray.wallX));
}

void	ray_floor(t_env *m)
{
	if (!m->ray.side && m->ray.raydirX > 0)
	{
		m->ray.floorX = m->ray.mapX;
		m->ray.floorY = m->ray.mapY + m->ray.wallX;
	}
	else if (!m->ray.side && m->ray.raydirX < 0)
	{
		m->ray.floorX = m->ray.mapX + 1.0;
		m->ray.floorY = m->ray.mapY + m->ray.wallX;
	}
	else if (m->ray.side == 1 && m->ray.raydirY > 0)
	{
		m->ray.floorX = m->ray.mapX + m->ray.wallX;
		m->ray.floorY = m->ray.mapY;
	}
	else
	{
		m->ray.floorX = m->ray.mapX + m->ray.wallX;
		m->ray.floorY = m->ray.mapY + 1.0;
	}
}

void	raycasting(t_env *m)
{
	int		x;

	ft_bzero(m->data, WINDOW * WINDOW * 4);
	x = -1;
	while (++x < WINDOW)
	{
		ray_prep(m, x);
		ray_dda(m);
		ray_wall(m);
		plot_sky(m, x);
		plot_wall(m, x);
		ray_floor(m);
		plot_floor(m, x);
	}
}
