/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksonu <ksonu@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 22:00:08 by ksonu             #+#    #+#             */
/*   Updated: 2018/06/01 00:28:08 by ksonu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void		wolf(t_env *m, t_ray *r)
{
	int		x;
	int		y;
	int		hit;
	int		side;
	double	perpwalldis;

	hit = 0;
	x = -1;
	while (++x < m->map.wid)
	{
		r->cameraX = 2 * x / ((double)m->map.wid - 1);
		r->raydirX = r->dirX + r->planeX * cameraX;
		r->raydirY = r->dirY + r->planeY * cameraX;
		r->mapX = (int)r->posX;
		r->mapY = (int)r->posY;
		r->deltadisX = sqrt(1 + (r->raydirY * r->raydirY) / (r->raydirX * r->raydirX));
		r->deltadisY = sqrt(1 + (r->raydirX * r->raydirX) / (r->raydirY * r->raydirY));
		if (r->raydirX < 0)
		{
			r->stepX = -1;
			r->sidedistX = (r->posX - r->mapX) * deltadistX;
		}
		else
		{
			r->stepX = 1;
			r->sidedistX = (r->mapX + 1.0 - r->posX) * deltadistX;
		}
		if (r->raydirY < 0)
		{
			r->stepY = -1;
			r->sidedistY = (r->posY - r->mapY) * deltadistY;
		}
		else
		{
			r->stepY = 1;
			r->sidedistY = (r->mapY + 1.0 - r->posY) * deltadistY;
		}
		while (hit == 0)
		{
			if (r->sidedistX < r->sidedistY)
			{
				r->sidedistX += r->deltadistX;
				r->mapX += r->stepX;
				side = 0;
			}
			else
			{
				r->sidedistY += r->deltadistY;
				r->mapY += r->stepY;
				side = 1;
			}
			if (m->map.map[r->mapX][r->mapY] > 0)
				hit = 1;
		}
		if (side == 0)
			perpwalldist = (r->mapX - r->posX + (1 - r->stepX) / 2) / r->raydirX;
		else
			perpwalldist = (r->mapY - r->posY + (1 - r->stepY) / 2) / r->raydirY;
	}
}

void		draw(t_env *m)
{
	int		lineheight;
	int		drawstart;
	int		drawend;
	
	lineheight = (int)(m->map.col / perpwalldis);
	drawstart = -lineheight / 2 + m->map.col / 2;
	drawend = lineheight / 2 + m->map.col
	if (drawstart < 0)
		drawstart = 0;
}
