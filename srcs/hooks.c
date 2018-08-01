/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksonu <ksonu@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/05 17:09:43 by ksonu             #+#    #+#             */
/*   Updated: 2018/07/31 18:16:55 by ksonu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	key_right(int key, t_env *m)
{
	double	tmpdir_x;
	double	tmpplane_x;

	m->ray.movespeed = 0.1;
	if (key == 124)
	{
		tmpdir_x = m->ray.dirx;
		m->ray.dirx = m->ray.dirx * cos(-(m->ray.rotspeed)) -
			m->ray.diry * sin(-(m->ray.rotspeed));
		m->ray.diry = tmpdir_x * sin(-(m->ray.rotspeed)) +
			m->ray.diry * cos(-(m->ray.rotspeed));
		tmpplane_x = m->ray.planex;
		m->ray.planex = m->ray.planex * cos(-(m->ray.rotspeed)) -
			m->ray.planey * sin(-(m->ray.rotspeed));
		m->ray.planey = tmpplane_x * sin(-(m->ray.rotspeed)) +
			m->ray.planey * cos(-(m->ray.rotspeed));
	}
}

void	key_left(int key, t_env *m)
{
	double tmpdir_x;
	double tmpplane_x;

	m->ray.movespeed = 0.1;
	if (key == 123)
	{
		tmpdir_x = m->ray.dirx;
		m->ray.dirx = m->ray.dirx * cos(m->ray.rotspeed) -
			m->ray.diry * sin(m->ray.rotspeed);
		m->ray.diry = tmpdir_x * sin(m->ray.rotspeed) +
			m->ray.diry * cos(m->ray.rotspeed);
		tmpplane_x = m->ray.planex;
		m->ray.planex = m->ray.planex * cos(m->ray.rotspeed) -
			m->ray.planey * sin(m->ray.rotspeed);
		m->ray.planey = tmpplane_x * sin(m->ray.rotspeed) +
			m->ray.planey * cos(m->ray.rotspeed);
	}
}

void	key_speed(int key, t_env *m)
{
	system("afplay -t 0.5 ./sound/woo.wav &");
	if (key == 1)
	{
		m->ray.movespeed = 0.5;
		if (!m->map[(int)m->ray.posy][(int)(m->ray.posx +
					m->ray.dirx * m->ray.movespeed)].type)
			m->ray.posx += m->ray.dirx * m->ray.movespeed;
		if (!m->map[(int)(m->ray.posy + m->ray.diry * m->ray.movespeed)]
				[(int)m->ray.posx].type)
			m->ray.posy += m->ray.diry * m->ray.movespeed;
	}
}

void	key_updown(int key, t_env *m)
{
	if (key == 126)
	{
		if (!m->map[(int)m->ray.posy][(int)(m->ray.posx +
					m->ray.dirx * m->ray.movespeed)].type)
			m->ray.posx += m->ray.dirx * m->ray.movespeed;
		if (!m->map[(int)(m->ray.posy + m->ray.diry * m->ray.movespeed)]
				[(int)m->ray.posx].type)
			m->ray.posy += m->ray.diry * m->ray.movespeed;
	}
	if (key == 125)
	{
		if (!m->map[(int)m->ray.posy][(int)(m->ray.posx -
					m->ray.dirx * m->ray.movespeed)].type)
			m->ray.posx -= m->ray.dirx * m->ray.movespeed;
		if (!m->map[(int)(m->ray.posy - m->ray.diry * m->ray.movespeed)]
				[(int)m->ray.posx].type)
			m->ray.posy -= m->ray.diry * m->ray.movespeed;
	}
}

int		key_exit(t_env *m)
{
	int		i;

	system("killall afplay");
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
