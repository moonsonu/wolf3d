/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plot.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksonu <ksonu@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 16:39:24 by ksonu             #+#    #+#             */
/*   Updated: 2018/07/31 18:23:44 by ksonu            ###   ########.fr       */
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
		m->ray.currfloorx = m->ray.weight * m->ray.floorx +
			(1.0 - m->ray.weight) * m->ray.posx;
		m->ray.currfloory = m->ray.weight * m->ray.floory +
			(1.0 - m->ray.weight) * m->ray.posy;
		m->ray.floortextx = (int)(m->ray.currfloorx * TEXTWD) % (int)TEXTWD;
		m->ray.floortexty = (int)(m->ray.currfloory * TEXTHT) % (int)TEXTHT;
		m->data[y * (int)WINDOW + x] = ((m->texture[0][(int)(TEXTHT * m->ray.
						floortexty + m->ray.floortextx)]) >> 1) & 8355711;
	}
}

void	plot_sky(t_env *m, int x)
{
	int		y;

	y = -1;
	while (++y < WINDOW / 2)
	{
		m->ray.d = (y * 256 - WINDOW * 128 + m->ray.lineheight * 128);
		m->ray.texy = ((m->ray.d * TEXTHT) / m->ray.lineheight) / 256;
		m->data[y * ((int)WINDOW) + x] = m->texture[3][(int)(WINDOW * y + x)];
	}
}

void	plot_wall(t_env *m, int x)
{
	int		y;

	m->ray.texx = (int)(m->ray.wallx * (double)TEXTWD);
	if (m->ray.side == 0 && m->ray.raydirx > 0)
		m->ray.texx = TEXTWD - m->ray.texx - 1;
	if (m->ray.side == 1 && m->ray.raydiry < 0)
		m->ray.texx = TEXTWD - m->ray.texx - 1;
	y = m->ray.start - 1;
	while (++y < m->ray.end)
	{
		m->ray.d = y * 256 - WINDOW * 128 + m->ray.lineheight * 128;
		m->ray.texy = ((m->ray.d * TEXTHT) / m->ray.lineheight) / 256;
		if (m->ray.textnum != 3)
			m->ray.color = m->texture[m->ray.textnum][(int)(TEXTWD *
				m->ray.texy + m->ray.texx)];
		if (m->ray.side == 1)
			m->ray.color = (m->ray.color >> 1) & 8355711;
		m->data[y * ((int)WINDOW) + x] = m->ray.color;
	}
}
