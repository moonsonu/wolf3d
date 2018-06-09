/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksonu <ksonu@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 17:09:43 by ksonu             #+#    #+#             */
/*   Updated: 2018/06/08 19:02:08 by ksonu            ###   ########.fr       */
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
		m->ray.dirX = m->ray.dirX * cos(-(m->ray.rotspeed)) - m->ray.dirY * sin(-(m->ray.rotspeed));
		m->ray.dirY = tmpdir_x * sin(-(m->ray.rotspeed)) + m->ray.dirY * cos(-(m->ray.rotspeed));
		tmpplane_x = m->ray.planeX;
		m->ray.planeX = m->ray.planeX * cos(-(m->ray.rotspeed)) - m->ray.planeY * sin(-(m->ray.rotspeed));
		m->ray.planeY = tmpplane_x * sin(-(m->ray.rotspeed)) + m->ray.planeY * cos(-(m->ray.rotspeed));
	}
	if (key == 123)
	{
		tmpdir_x = m->ray.dirX;
		m->ray.dirX = m->ray.dirX * cos(m->ray.rotspeed) - m->ray.dirY * sin(m->ray.rotspeed);
		m->ray.dirY = tmpdir_x * sin(m->ray.rotspeed) + m->ray.dirY * cos(m->ray.rotspeed);
		tmpplane_x = m->ray.planeX;
		m->ray.planeX = m->ray.planeX * cos(m->ray.rotspeed) - m->ray.planeY * sin(m->ray.rotspeed);
		m->ray.planeY = tmpplane_x * sin(m->ray.rotspeed) + m->ray.planeY * cos(m->ray.rotspeed);
	}
}

void	key_updown(int key, t_env *m)
{
	if (key == 1)
	{
		m->ray.movespeed = 0.5;
		if (!m->map[(int)m->ray.posY][(int)(m->ray.posX +
					m->ray.dirX * m->ray.movespeed)].type)
			m->ray.posX += m->ray.dirX * m->ray.movespeed;
		if (!m->map[(int)(m->ray.posY + m->ray.dirY * m->ray.movespeed)]
				[(int)m->ray.posX].type)
			m->ray.posY += m->ray.dirY * m->ray.movespeed;
	}
	else if (key != 1)
		m->ray.movespeed = 0.1;
	if (key == 126)
	{
		if (!m->map[(int)m->ray.posY][(int)(m->ray.posX +
					m->ray.dirX * m->ray.movespeed)].type)
			m->ray.posX += m->ray.dirX * m->ray.movespeed;
		if (!m->map[(int)(m->ray.posY + m->ray.dirY * m->ray.movespeed)]
				[(int)m->ray.posX].type)
			m->ray.posY += m->ray.dirY * m->ray.movespeed;
	}
	if (key == 125)
	{
		if (!m->map[(int)m->ray.posY][(int)(m->ray.posX -
					m->ray.dirX * m->ray.movespeed)].type)
			m->ray.posX -= m->ray.dirX * m->ray.movespeed;
		if (!m->map[(int)(m->ray.posY - m->ray.dirY * m->ray.movespeed)]
				[(int)m->ray.posX].type)
			m->ray.posY -= m->ray.dirY * m->ray.movespeed;
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
	(key == 125 || key == 126 || key == 1) ? key_updown(key, m) : 0;
	raycasting(m);
	mlx_put_image_to_window(m->mlx_ptr, m->win_ptr, m->image, 0, 0);
	hand(m);
	return (0);
}
