/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksonu <ksonu@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/23 21:03:33 by ksonu             #+#    #+#             */
/*   Updated: 2018/07/25 18:25:47 by ksonu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	parse_sprite(t_env *m)
{
	int		i;
	int		j;
	int		k;

	i = -1;
	k = -1;
	while (++i < m->map_maxy)
	{
		j = -1;
		while (++j < m->map_maxx)
		{
			if (m->map[i][j].type == 3)
			{
				while (++k < m->ray.numsprite)
				{
					m->sprite[k].x = j;
					m->sprite[k].y = i;
					m->sprite[k].texture = 3;
				}
			}
		}
	}
	init_sprite(m);
}

void	init_sprite(t_env *m)
{
	m->spt.spriteorder = ft_memalloc(sizeof(int*) * (m->ray.numsprite + 1));
	m->spt.spritedistance = ft_memalloc(sizeof(int*) * (m->ray.numsprite + 1));
	m->spt.zbuffer = ft_memalloc(sizeof(double*) * WINDOW);
}

void	ray_sprite(t_env *m, int x)
{
	int		i;
	int		y;

/*	i = -1;
	while (++i < m->ray.numsprite)
	{
		m->spt.spriteorder[i] = i;
		//m->spt.spritedistance[i] = ((m->ray.posX - m->sprite[i].x) * (m->ray.posX - m->sprite[i].x) + (m->ray.posY - m->sprite[i].y) * (m->ray.posY - m->sprite[i].y));
	}*/
	i = -1;
	while (++i < m->ray.numsprite)
	{
		m->spt.spriteX = m->sprite[i].x - m->ray.posX;
		m->spt.spriteY = m->sprite[i].y - m->ray.posY;
		m->spt.invdet = 1.0 / (m->ray.planeX * m->ray.dirY - m->ray.dirX * m->ray.planeY);
		m->spt.transformX = m->spt.invdet * (m->ray.dirY * m->spt.spriteX - m->ray.dirX * m->spt.spriteY);
		m->spt.transformY = m->spt.invdet * (-m->ray.planeY * m->spt.spriteX + m->ray.planeX * m->spt.spriteY);
		m->spt.spritescreenX = (int)((WINDOW / 2) * (1 + m->spt.transformX / m->spt.transformY));
		m->spt.spriteheight = abs((int)(WINDOW / m->spt.transformY));
		m->spt.drawstartY = -m->spt.spriteheight / 2 + WINDOW / 2;
		if (m->spt.drawstartY < 0)
			m->spt.drawstartY = 0;
		m->spt.drawendY = m->spt.spriteheight / 2 + WINDOW / 2;
		if (m->spt.drawendY >= WINDOW)
			m->spt.drawendY = WINDOW - 1;
		m->spt.spritewidth = abs((int)(WINDOW / m->spt.transformY));
		m->spt.drawstartX = -m->spt.spritewidth / 2 + m->spt.spritescreenX;
		if (m->spt.drawstartX < 0)
			m->spt.drawstartX = 0;
		m->spt.drawendX = m->spt.spritewidth / 2 + m->spt.spritescreenX;
		if (m->spt.drawendX >= WINDOW)
			m->spt.drawendX = WINDOW - 1;
		m->spt.stripe = m->spt.drawstartX - 1;
		while (++(m->spt.stripe) < m->spt.drawendX)
		{
			m->spt.s_texX = (int)(256 * (m->spt.stripe - (-m->spt.spritewidth / 2 + m->spt.spritescreenX)) * TEXTWD / m->spt.spritewidth) / 256;
			if (m->spt.transformY > 0 && m->spt.stripe > 0 && m->spt.stripe < WINDOW && m->spt.transformY < m->spt.zbuffer[m->spt.stripe])
			{
				y = m->spt.drawstartY - 1;
				while(++y < m->spt.drawendY)
				{
					m->spt.d = y * 256 - WINDOW * 128 + m->spt.spriteheight * 128;
					m->spt.s_texY = ((m->spt.d * TEXTHT) / m->spt.spriteheight) / 256;
					m->data[y * ((int)WINDOW) + x] = m->texture[6][(int)(m->xpm.xpm_s_x * m->spt.s_texY + m->spt.s_texX)];
				}
			}
		}
	}
}
