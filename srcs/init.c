/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksonu <ksonu@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 21:58:17 by ksonu             #+#    #+#             */
/*   Updated: 2018/05/31 22:24:02 by ksonu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	init_mlx(t_env *m)
{
	m->mlx_ptr = mlx_init();
	m->win_ptr = mlx_new_window(m->mlx_ptr, WIN, WIN, "WOLF3D - ksonu");
	m->image = mlx_new_image(m->mlx_ptr, WIN, WIN);
	m->data = (int*)mlx_get_data_addr(m->image, &m->bbp, &m->size, &m->endian);
}

void	init_env(t_env *m)
{
	m->posX = 22;
	m->posY = 12;
	m->dirX = -1;
	m->dirY = 0;
	m->planeX = 0;
	m->planeY = 0.66;
}
