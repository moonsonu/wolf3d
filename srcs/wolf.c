/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksonu <ksonu@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 22:00:08 by ksonu             #+#    #+#             */
/*   Updated: 2018/06/04 22:14:24 by ksonu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
/*void		plot_floor(t_env *m, int x, int end)
{
	int		y;

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
	else if (m->ray.side && m->ray.raydirY > 0)
	{
		m->ray.floorX = m->ray.mapX + m->ray.wallX;
		m->ray.floorY = m->ray.mapY;
	}
	else
	{
		m->ray.floorX = m->ray.mapX + m->ray.wallX;
		m->ray.floorY = m->ray.mapY + 1.0;
	}
	m->ray.distwall = m->ray.perpwalldist;
	m->ray.distpos = 0;
	y = end + 1;
	while (y++ < WINDOW)
	{
		m->ray.distcurr = WINDOW / (2.0 * y - WINDOW);
		m->ray.weight = (m->ray.distcurr - m->ray.distpos) / (m->ray.distwall - m->ray.distpos);
		m->ray.currfloorX = m->ray.weight * m->ray.floorX + (1.0 - m->ray.weight) * m->ray.posX;
		m->ray.currfloorY = m->ray.weight * m->ray.floorY + (1.0 - m->ray.weight) * m->ray.posY;
		m->ray.floortextX = (int)(m->ray.currfloorX * TEXTWD) % TEXTWD;
		m->ray.floortextY = (int)(m->ray.currfloorY * TEXTHT) % TEXTHT;
		m->data[x + (y * m->size) / 4] = (m->texture[3]
				[TEXTHT * m->ray.floortextY + m->ray.floortextX] >> 1) & 8355711;
		m->data[x + ((WINDOW - y) * m->size) / 4] =
			m->texture[6][TEXTHT * m->ray.floortextY + m->ray.floortextX];
	}
}

void		plot(t_env *m, int x, int start, int end)
  {
  int		d;
//int		textnum;
int		texX;
int		texY;
int		color;
int		y;

//textnum = m->map.map[m->ray.mapY][m->ray.mapX];
//printf("textnum[%d]\n", textnum);
if (m->ray.side == 0)
m->ray.wallX = m->ray.posY + m->ray.perpwalldist * m->ray.raydirY;
else
m->ray.wallX = m->ray.posX + m->ray.perpwalldist * m->ray.raydirX;
m->ray.wallX -= floor((m->ray.wallX));
texX = (int)(m->ray.wallX * TEXTWD);
if (m->ray.side == 0 && m->ray.raydirX > 0)
texX = TEXTWD - texX - 1;
if (m->ray.side == 1 && m->ray.raydirY < 0)
texX = TEXTWD - texX - 1;
y = start - 1;
while (++y < end)
{
d = start * 256 - WINDOW * 128 + m->ray.lineheight * 128;
texY = ((d * TEXTHT) / m->ray.lineheight) / 256;
color = m->texture[0][TEXTHT * texY + texX];
if (m->ray.side == 1)
color = (color >> 1) & 8355711;
m->data[y * ((int)WINDOW) + x] = color;
}
}*/

void		wolf(t_env *m, int x)
{
	m->ray.cameraX = 2 * x / ((double)WINDOW - 1);
	m->ray.raydirX = m->ray.dirX + m->ray.planeX * m->ray.cameraX;
	m->ray.raydirY = m->ray.dirY + m->ray.planeY * m->ray.cameraX;
	m->ray.mapX = (int)m->ray.posX;
	m->ray.mapY = (int)m->ray.posY;
	m->ray.deltadistX = fabs(1 / m->ray.raydirX);
	m->ray.deltadistY = fabs(1 / m->ray.raydirY);
	m->ray.hit = 0;
	if (m->ray.raydirX < 0)
	{
		m->ray.stepX = -1;
		m->ray.sidedistX = (m->ray.posX - m->ray.mapX) * m->ray.deltadistX;
	}
	else
	{
		m->ray.stepX = 1;
		m->ray.sidedistX = (m->ray.mapX + 1.0 - m->ray.posX) * m->ray.deltadistX;
	}
	if (m->ray.raydirY < 0)
	{
		m->ray.stepY = -1;
		m->ray.sidedistY = (m->ray.posY - m->ray.mapY) * m->ray.deltadistY;
	}
	else
	{
		m->ray.stepY = 1;
		m->ray.sidedistY = (m->ray.mapY + 1.0 - m->ray.posY) * m->ray.deltadistY;
	}
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
		if (m->map.map[m->ray.mapY][m->ray.mapX] > 0)
			m->ray.hit = 1;
	}
}

void		raycasting(t_env *m)
{
	int		x;
	int		y;

	ft_bzero(m->data, WINDOW * WINDOW * 4);
	x = -1;
	while (++x < WINDOW)
	{
		wolf(m, x);
		ray_dda(m);
		if (m->ray.side == 0)
			m->ray.perpwalldist = (m->ray.mapX - m->ray.posX + (1 - m->ray.stepX) / 2) / m->ray.raydirX;
		else
			m->ray.perpwalldist = (m->ray.mapY - m->ray.posY + (1 - m->ray.stepY) / 2) / m->ray.raydirY;

		m->ray.lineheight = (int)(WINDOW / m->ray.perpwalldist);
		m->ray.start = -(m->ray.lineheight) / 2 + WINDOW / 2;
		if (m->ray.start < 0)
			m->ray.start = 0;
		m->ray.end = m->ray.lineheight / 2 + WINDOW / 2;
		if (m->ray.end >= WINDOW)
			m->ray.end = WINDOW - 1;
		//plot(m, x, start, end);
		//int		textnum;

		//textnum = m->map.map[m->ray.mapY][m->ray.mapX];
		//printf("textnum[%d]\n", textnum);
		if (m->ray.side == 0)
			m->ray.wallX = m->ray.posY + m->ray.perpwalldist * m->ray.raydirY;
		else
			m->ray.wallX = m->ray.posX + m->ray.perpwalldist * m->ray.raydirX;
		m->ray.wallX -= floor((m->ray.wallX));
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
			m->ray.color = m->texture[0][(int)(TEXTWD * m->ray.texY + m->ray.texX)];
			if (m->ray.side == 1)
				m->ray.color = (m->ray.color >> 1) & 8355711;
			m->data[y * ((int)WINDOW) + x] = m->ray.color;
		}
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
		else if (m->ray.side && m->ray.raydirY > 0)
		{
			m->ray.floorX = m->ray.mapX + m->ray.wallX;
			m->ray.floorY = m->ray.mapY;
		}
		else
		{
			m->ray.floorX = m->ray.mapX + m->ray.wallX;
			m->ray.floorY = m->ray.mapY + 1.0;
		}
		m->ray.distwall = m->ray.perpwalldist;
		m->ray.distpos = 0.0;
		if (m->ray.end < 0)
			m->ray.end = WINDOW;
		y = m->ray.end;
		while (++y < WINDOW)
		{
			m->ray.distcurr = WINDOW / (2.0 * y - WINDOW);
			m->ray.weight = (m->ray.distcurr - m->ray.distpos) / (m->ray.distwall - m->ray.distpos);
			m->ray.currfloorX = m->ray.weight * m->ray.floorX + (1.0 - m->ray.weight) * m->ray.posX;
			m->ray.currfloorY = m->ray.weight * m->ray.floorY + (1.0 - m->ray.weight) * m->ray.posY;
			m->ray.floortextX = (int)(m->ray.currfloorX * TEXTWD) % (int)TEXTWD;
			m->ray.floortextY = (int)(m->ray.currfloorY * TEXTHT) % (int)TEXTHT;
			m->data[y * (int)WINDOW + x] = (m->texture[1]
					[(int)(TEXTHT * m->ray.floortextY + m->ray.floortextX)] >> 1) & 8355711;
			m->data[(int)(WINDOW - y) * WINDOW + x] =
				m->texture[2][(int)(TEXTHT * m->ray.floortextY + m->ray.floortextX)];
		}
		//plot_floor(m, x, end);
	}
}
