/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksonu <ksonu@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 17:09:43 by ksonu             #+#    #+#             */
/*   Updated: 2018/06/06 21:15:13 by ksonu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	key_leftright(int key, t_env *m)
{
	double	tmpdir_x;
	double	tmpplane_x;
	
	if (key == 124)
	{
		tmpdir_x = m->ray.dirX;
		m->ray.dirX = m->ray.dirX * cos(-0.1) - m->ray.dirY * sin(-0.1);
		m->ray.dirY = tmpdir_x * sin(-0.1) + m->ray.dirY * cos(-0.1);
		tmpplane_x = m->ray.planeX;
		m->ray.planeX = m->ray.planeX * cos(-0.1) - m->ray.planeY * sin(-0.1);
		m->ray.planeY = tmpplane_x * sin(-0.1) + m->ray.planeY * cos(-0.1);
	}
	if (key == 123)
	{
		tmpdir_x = m->ray.dirX;
		m->ray.dirX = m->ray.dirX * cos(0.1) - m->ray.dirY * sin(0.1);
		m->ray.dirY = tmpdir_x * sin(0.1) + m->ray.dirY * cos(0.1);
		tmpplane_x = m->ray.planeX;
		m->ray.planeX = m->ray.planeX * cos(0.1) - m->ray.planeY * sin(0.1);
		m->ray.planeY = tmpplane_x * sin(0.1) + m->ray.planeY * cos(0.1);
	}
}

void	key_updown(int key, t_env *m)
{
	if (key == 126)
	{
		if (!m->map[(int)m->ray.posY][(int)(m->ray.posX +
					m->ray.dirX * 0.1)].type)
			m->ray.posX += m->ray.dirX * 0.1;
		if (!m->map[(int)(m->ray.posY + m->ray.dirY * 0.1)]
				[(int)m->ray.posX].type)
			m->ray.posY += m->ray.dirY * 0.1;
	}
	if (key == 125)
	{
		if (!m->map[(int)m->ray.posY][(int)(m->ray.posX -
					m->ray.dirX * 0.1)].type)
			m->ray.posX -= m->ray.dirX * 0.1;
		if (!m->map[(int)(m->ray.posY - m->ray.dirY * 0.1)]
				[(int)m->ray.posX].type)
			m->ray.posY -= m->ray.dirY * 0.1;
	}
}

int		key_exit(t_env *m)
{
	int		i;

	if (m->image)
		mlx_destroy_image(m->mlx_ptr, m->image);
	if (m->win_ptr)
		mlx_destroy_window(m->mlx_ptr, m->win_ptr);
	if (m->map)
	{
		i = -1;
		while (m->map[++i])
			free(m->map[i]);
		free(m->map);
	}
	if (m->texture[0])
	{
		i = -1;
		while (++i < 4)
			free(m->texture[i]);
	}
	exit(0);
}

int		keyfunction(int key, t_env *m)
{
	ft_bzero(m->data, WINDOW * WINDOW * 4);
	key == 53 ? exit(0) : 0;
	(key == 123 || key == 124) ? key_leftright(key, m) : 0;
	(key == 125 || key == 126) ? key_updown(key, m) : 0;
	raycasting(m);
	mlx_put_image_to_window(m->mlx_ptr, m->win_ptr, m->image, 0, 0);
	return (0);
}
