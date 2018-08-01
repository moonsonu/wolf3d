/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksonu <ksonu@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 22:00:08 by ksonu             #+#    #+#             */
/*   Updated: 2018/07/31 18:28:23 by ksonu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	ray_prep(t_env *m, int x)
{
	m->ray.camerax = 2 * x / (double)WINDOW - 1;
	m->ray.raydirx = m->ray.dirx + m->ray.planex * m->ray.camerax;
	m->ray.raydiry = m->ray.diry + m->ray.planey * m->ray.camerax;
	m->ray.mapx = (int)m->ray.posx;
	m->ray.mapy = (int)m->ray.posy;
	m->ray.deltadistx = fabs(1 / m->ray.raydirx);
	m->ray.deltadisty = fabs(1 / m->ray.raydiry);
	m->ray.hit = 0;
	m->ray.stepx = (m->ray.raydirx < 0) ? -1 : 1;
	(m->ray.raydirx < 0) ? (m->ray.sidedistx = (m->ray.posx - m->ray.mapx) *
			m->ray.deltadistx) : (m->ray.sidedistx = (m->ray.mapx + 1.0 -
					m->ray.posx) * m->ray.deltadistx);
	m->ray.stepy = (m->ray.raydiry < 0) ? -1 : 1;
	(m->ray.raydiry < 0) ? (m->ray.sidedisty = (m->ray.posy - m->ray.mapy) *
			m->ray.deltadisty) : (m->ray.sidedisty = (m->ray.mapy + 1.0 -
					m->ray.posy) * m->ray.deltadisty);
}

void	ray_dda(t_env *m)
{
	while (m->ray.hit == 0)
	{
		if (m->ray.sidedistx < m->ray.sidedisty)
		{
			m->ray.sidedistx += m->ray.deltadistx;
			m->ray.mapx += m->ray.stepx;
			m->ray.side = 0;
		}
		else
		{
			m->ray.sidedisty += m->ray.deltadisty;
			m->ray.mapy += m->ray.stepy;
			m->ray.side = 1;
		}
		if (m->map[m->ray.mapy][m->ray.mapx].type > 0)
		{
			m->ray.hit = 1;
			m->ray.textnum = m->map[m->ray.mapy][m->ray.mapx].type;
		}
	}
}

void	ray_wall(t_env *m)
{
	if (m->ray.side == 0)
		m->ray.perpwalldist = (m->ray.mapx - m->ray.posx +
				(1 - m->ray.stepx) / 2) / m->ray.raydirx;
	else
		m->ray.perpwalldist = (m->ray.mapy - m->ray.posy +
				(1 - m->ray.stepy) / 2) / m->ray.raydiry;
	m->ray.lineheight = (int)(WINDOW / m->ray.perpwalldist);
	m->ray.start = -(m->ray.lineheight) / 2 + WINDOW / 2;
	if (m->ray.start < 0)
		m->ray.start = 0;
	m->ray.end = m->ray.lineheight / 2 + WINDOW / 2;
	if (m->ray.end >= WINDOW)
		m->ray.end = WINDOW - 1;
	if (m->ray.side == 0)
		m->ray.wallx = m->ray.posy + m->ray.perpwalldist * m->ray.raydiry;
	else
		m->ray.wallx = m->ray.posx + m->ray.perpwalldist * m->ray.raydirx;
	m->ray.wallx -= floor((m->ray.wallx));
}

void	ray_floor(t_env *m)
{
	if (!m->ray.side && m->ray.raydirx > 0)
	{
		m->ray.floorx = m->ray.mapx;
		m->ray.floory = m->ray.mapy + m->ray.wallx;
	}
	else if (!m->ray.side && m->ray.raydirx < 0)
	{
		m->ray.floorx = m->ray.mapx + 1.0;
		m->ray.floory = m->ray.mapy + m->ray.wallx;
	}
	else if (m->ray.side == 1 && m->ray.raydiry > 0)
	{
		m->ray.floorx = m->ray.mapx + m->ray.wallx;
		m->ray.floory = m->ray.mapy;
	}
	else
	{
		m->ray.floorx = m->ray.mapx + m->ray.wallx;
		m->ray.floory = m->ray.mapy + 1.0;
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
		minimap(m);
	}
	plot_car(m);
}
