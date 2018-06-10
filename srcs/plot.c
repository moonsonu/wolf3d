/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksonu <ksonu@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 16:39:24 by ksonu             #+#    #+#             */
/*   Updated: 2018/06/09 21:25:45 by ksonu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#define UDIV 1
#define VDIV 1
#define VMOVE 0.0

/*void	plot_sprite(t_env *m, int x)
{
	int		i;
	int		stripe;
	int		y;

	i = -1;
	m->data[x] = m->ray.perpwalldist;
	while (++i < m->numsprites)
	{
		m->spt.spriteorder[i] = i;
		m->spt.spritedistance[i] = ((m->ray.posX - m->sprite[i].x) * (m->ray.posX - m->sprite[i].x) + (m->ray.posY - m->sprite[i].y) * (m->ray.posY - m->sprite[i].y));
	}
	i = -1;
	while (++i < m->numsprites)
	{
		m->spt.spriteX = m->sprite[m->spt.spriteorder[i]].x - m->ray.posX;
		m->spt.spriteY = m->sprite[m->spt.spriteorder[i]].y - m->ray.posY;
		m->spt.transformX = m->spt.invdet * (m->ray.dirY * m->spt.spriteX - m->ray.dirX * m->spt.spriteY);
		m->spt.transformY = m->spt.invdet * (-(m->ray.planeY) * m->spt.spriteX + m->ray.planeX * m->spt.spriteY);
		m->spt.spritescreenX = int((WINDOW / 2) * (1 + m->spt.transformX / m->spt.transformY));
		m->spt.vmovescreen = int(VMOVE / m->spt.transformY);
		m->spt.spriteheight = fabs(int(WINDOW / m->spt.transformY)) / VDIV;
		m->spt.drawstartY = -(m->spt.spriteheight) / 2 + WINDOW / 2 + m->spt.vmovescreen;
		if (m->spt.drawstartY < 0)
			m->spt.drawstartY = 0;
		m->spt.drawendY = m->spt.spriteheight / 2 + WINDOW / 2 + m->spt.vmovescreen;
		if (m->spt.drawendY >= WINDOW)
			m->spt.drawendY = WINDOW - 1;
		m->spt.spritewidth = fabs(int(WINDOW / m->spt.transformY)) / UDIV;
		m->spt.drawstartX = -(m->spt.spritewidth) / 2 + m->spt.spritescreenX;
		if (m->spt.drawstartX < 0)
			m->spt.drawstartX = 0;
		m->spt.drawendX = m->spt.spritewidth / 2 + m->spt.spritescreenX;
		if (m->spt.drawendX >= WINDOW)
			m->spt.drawendX = WINDOW - 1;
		stripe = m->spt.drawstartX - 1;
		while (++stripe < m->spt.drawendX)
		{
			m->spt.s_texX = int(256 * (stripe - (m->spt.spritewidth / 2 + m->spt.spritescreenX)) * TEXTWD / m->spt.spritewidth) / 256;
			if (m->spt.transformY > 0 && stripe > 0 && stripe < WINDOW && m->spt.transformY < m->data[stripe])
			{
				y = m->spt.drawstartY;
				while (y++ < m->spt.drawendY)
				{
					m->spt.s_d = (y - m->spt.vmovescreen) * 256 - h * 128 + m->spt.spriteheight * 128;
					m->spt.s_texY = ((m->spt.s_d * TEXTHT) / m->spt.spriteheight) / 256;
					m->ray.color = m->texture[m->sprite[m->spt.spriteorder[i]].texture][TEXTWD * m->spt.s_texY + m->spt.s_texX];
					if ((color & 0x00FFFFFF) != 0)
						m->data[y * stripe] = color;
	}
}*/

void	plot_car(t_env *m)
{
	t_env	h;
	int		x;
	int		y;
	int		i;

	i = 0;
	y = -1;
	//ft_bzero(&h, sizeof(h));
	h.image = mlx_new_image(m->mlx_ptr, (m->xpm.xpm_h_x), (m->xpm.xpm_h_y));
	h.data = (int*)mlx_get_data_addr(h.image, &m->bbp, &m->size, &m->endian);
	while (++y < m->xpm.xpm_h_y)
	{
		x = -1;
		while (++x < m->xpm.xpm_h_x)
			h.data[(y * m->xpm.xpm_h_x) + x] = m->texture[4][i++];
	}
	mlx_put_image_to_window(m->mlx_ptr, m->win_ptr, h.image, 0, 0);
}

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
		m->ray.weight = (m->ray.distcurr - m->ray.distpos) /
			(m->ray.distwall - m->ray.distpos);
		m->ray.currfloorX = m->ray.weight * m->ray.floorX +
			(1.0 - m->ray.weight) * m->ray.posX;
		m->ray.currfloorY = m->ray.weight * m->ray.floorY +
			(1.0 - m->ray.weight) * m->ray.posY;
		m->ray.floortextX = (int)(m->ray.currfloorX * TEXTWD) % (int)TEXTWD;
		m->ray.floortextY = (int)(m->ray.currfloorY * TEXTHT) % (int)TEXTHT;
		m->data[y * (int)WINDOW + x] = ((m->texture[0][(int)(TEXTHT *
						m->ray.floortextY + m->ray.floortextX)]) >> 1)
			& 8355711;
	/*	m->data[(int)(WINDOW - y) * WINDOW + x] = m->texture[3][(int)(TEXTHT
				* m->ray.floortextY + m->ray.floortextX)];*/
	}
}

void	plot_sky(t_env *m, int x)
{
	int		y;

	y = -1;
	//m->ray.texX = (int)(m->ray.wallX * (double)TEXTWD);
	while (++y < 500)
	{
		m->ray.d = (y * 256 - WINDOW * 128 + m->ray.lineheight * 128);
		m->ray.texY = ((m->ray.d * TEXTHT) / m->ray.lineheight) / 256;
		m->data[y * ((int)WINDOW) + x] = m->texture[3][(int)(WINDOW * y + x)];
	}
}


void	plot_wall(t_env *m, int x)
{
	int		y;

	m->ray.texX = (int)(m->ray.wallX * (double)TEXTWD);
	if (m->ray.side == 0 && m->ray.raydirX > 0)
		m->ray.texX = TEXTWD - m->ray.texX - 1;
	if (m->ray.side == 1 && m->ray.raydirY < 0)
		m->ray.texX = TEXTWD - m->ray.texX - 1;
	y = m->ray.start - 1;
	while (++y < m->ray.end)
	{
		m->ray.d = y * 256 - WINDOW * 128 + m->ray.lineheight * 128;
		m->ray.texY = ((m->ray.d * TEXTHT) / m->ray.lineheight) / 256;
		m->ray.color = m->texture[m->ray.textnum][(int)(TEXTWD *
				m->ray.texY + m->ray.texX)];
		if (m->ray.side == 1)
			m->ray.color = (m->ray.color >> 1) & 8355711;
		m->data[y * ((int)WINDOW) + x] = m->ray.color;
	}
}
