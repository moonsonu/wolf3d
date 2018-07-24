/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksonu <ksonu@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 16:39:24 by ksonu             #+#    #+#             */
/*   Updated: 2018/07/24 14:16:03 by ksonu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	plot_car(t_env *m)
{
	t_env	h;
	int		x;
	int		y;
	int		i;

	i = 0;
	y = -1;
	ft_bzero(&h, sizeof(h));
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
		m->data[y * (int)WINDOW + x] = ((m->texture[0][(int)(TEXTHT * m->ray.
						floortextY + m->ray.floortextX)]) >> 1) & 8355711;
	}
}

void	plot_sky(t_env *m, int x)
{
	int		y;

	y = -1;
	while (++y < WINDOW / 2)
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
		if (m->ray.textnum != 3)
			m->ray.color = m->texture[m->ray.textnum][(int)(TEXTWD *
				m->ray.texY + m->ray.texX)];
		else if (m->ray.textnum == 3)
			m->ray.color = m->texture[6][(m->xpm.xpm_s_y * m->ray.texY + m->ray.texX)];
		if (m->ray.side == 1)
			m->ray.color = (m->ray.color >> 1) & 8355711;
		m->data[y * ((int)WINDOW) + x] = m->ray.color;
	}
}
