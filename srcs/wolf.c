/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksonu <ksonu@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 22:00:08 by ksonu             #+#    #+#             */
/*   Updated: 2018/06/01 22:31:15 by ksonu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		plot(t_env *m, int x, int start, int end)
{
	int		d;
	int		textnum;
	int		texX;
	int		texY;
	int		color;
	int		y;

	textnum = m->map.map[m->ray.mapX][m->ray.mapY];
	if (m->ray.side == 0)
		m->ray.wallX = m->ray.posX + m->ray.perpwalldist * m->ray.raydirY;
	else
		m->ray.wallX = m->ray.posX + m->ray.perpwalldist * m->ray.raydirX;
	m->ray.wallX -= floor((m->ray.wallX));
	texX = (int)(m->ray.wallX * TEXTWD);
	if (m->ray.side == 0 && m->ray.raydirX > 0)
		texX = TEXTWD - texX - 1;
	if (m->ray.side == 1 && m->ray.raydirY < 0)
		texX = TEXTWD - texX - 1;
	while (start < end)
	{
		d = start * 256 - WINDOW * 128 + m->ray.lineheight * 128;
		texY = ((d * TEXTHT) / m->ray.lineheight) / 256;
		color = m->texture[textnum][TEXTHT * texY + texX];
		if (m->ray.side == 1)
			color = (color >> 1) & 8355711;
		m->data[x + (start++ * m->size) / 4] = color;
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
	m->ray.distpos = 0;
	y = end + 1;
	while (++y < WINDOW)
	{
		m->ray.distcurr = WINDOW / (2.0 * y - WINDOW);
		m->ray.weight = (m->ray.distcurr - m->ray.distpos) / (m->ray.distwall - m->ray.distpos);
		m->ray.currfloorX = m->ray.weight * m->ray.floorX + (1.0 - m->ray.weight) * m->ray.posX;
		m->ray.currfloorY = m->ray.weight * m->ray.floorY + (1.0 - m->ray.weight) * m->ray.posY;
		m->ray.floortextX = (int)(m->ray.currfloorX * TEXTHT) % TEXTHT;
		m->ray.floortextY = (int)(m->ray.currfloorY * TEXTHT) % TEXTHT;
		m->data[x + (y * m->size) / 4] = (m->texture[4]
		[TEXTHT * m->ray.floortextY + m->ray.floortextX] >> 1) & 8355711;
		m->data[x + ((WINDOW - y) * m->size) / 4] =
		m->texture[5][TEXTHT * m->ray.floortextY + m->ray.floortextX];
	}

}

void		wolf(t_env *m, t_ray *r, int x)
{
	r->cameraX = 2 * x / (m->map.row - 1);
	r->raydirX = r->dirX + r->planeX * r->cameraX;
	r->raydirY = r->dirY + r->planeY * r->cameraX;
	r->mapX = (int)r->posX;
	r->mapY = (int)r->posY;
	r->deltadistX = sqrt(1 + (r->raydirY * r->raydirY) / (r->raydirX * r->raydirX));
	r->deltadistY = sqrt(1 + (r->raydirX * r->raydirX) / (r->raydirY * r->raydirY));
	r->hit = 0;
	if (r->raydirX < 0)
	{
		r->stepX = -1;
		r->sidedistX = (r->posX - r->mapX) * r->deltadistX;
	}
	else
	{
		r->stepX = 1;
		r->sidedistX = (r->mapX + 1.0 - r->posX) * r->deltadistX;
	}
	if (r->raydirY < 0)
	{
		r->stepY = -1;
		r->sidedistY = (r->posY - r->mapY) * r->deltadistY;
	}
	else
	{
		r->stepY = 1;
		r->sidedistY = (r->mapY + 1.0 - r->posY) * r->deltadistY;
	}
}

void	ray_dda(t_env *m, t_ray *r)
{
	while (r->hit == 0)
	{
		if (r->sidedistX < r->sidedistY)
		{
			r->sidedistX += r->deltadistX;
			r->mapX += r->stepX;
			r->side = 0;
		}
		else
		{
			r->sidedistY += r->deltadistY;
			r->mapY += r->stepY;
			r->side = 1;
		}
		if (m->map.map[r->mapY][r->mapX] > 0)
			r->hit = 1;
	}
}

void		raycasting(t_env *m, t_ray *r)
{
	int		x;
	int		start;
	int		end;

	ft_bzero(m->data, WINDOW * WINDOW * 4);
	x = -1;
	while (++x < WINDOW)
	{
		wolf(m, r, x);
		raycasting(m, r);
		if (r->side == 0)
			r->perpwalldist = (r->mapX - r->posX + (1 - r->stepX) / 2) / r->raydirX;
		else
			r->perpwalldist = (r->mapY - r->posY + (1 - r->stepY) / 2) / r->raydirY;

		r->lineheight = (int)(WINDOW / r->perpwalldist);
		start = -(r->lineheight) / 2 + WINDOW / 2;
		end = r->lineheight / 2 + WINDOW / 2;
		if (start < 0)
			start = 0;
		if (end >= WINDOW)
			end = WINDOW - 1;
		plot(m, x, start, end);
	}
}
