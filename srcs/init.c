/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksonu <ksonu@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 21:58:17 by ksonu             #+#    #+#             */
/*   Updated: 2018/06/06 16:24:48 by ksonu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	init_mlx(t_env *m)
{
	//m->mlx_ptr = mlx_init();
	//m->win_ptr = mlx_new_window(m->mlx_ptr, WINDOW, WINDOW, "WOLF");
	m->image = mlx_new_image(m->mlx_ptr, WINDOW, WINDOW);
	m->data = (int*)mlx_get_data_addr(m->image, &m->bbp, &m->size, &m->endian);
	m->xpm.xpm_floor = mlx_xpm_file_to_image(m->mlx_ptr, "./xpm/bluestone.xpm", &(m->xpm.xpm_f_x), &(m->xpm.xpm_f_y));
	m->xpm.xpm_f_addr = (int*)mlx_get_data_addr(m->xpm.xpm_floor, &(m->xpm.xpm_f_b), &(m->xpm.xpm_f_s), &(m->xpm.xpm_f_e));
	m->xpm.xpm_wall = mlx_xpm_file_to_image(m->mlx_ptr, "./xpm/greystone.xpm", &(m->xpm.xpm_w_x), &(m->xpm.xpm_w_y));
	m->xpm.xpm_w_addr = (int*)mlx_get_data_addr(m->xpm.xpm_wall, &(m->xpm.xpm_w_b), &(m->xpm.xpm_w_s), &(m->xpm.xpm_w_e));
	m->xpm.xpm_block = mlx_xpm_file_to_image(m->mlx_ptr, "./xpm/redbrick.xpm", &(m->xpm.xpm_b_x), &(m->xpm.xpm_b_y));
	m->xpm.xpm_b_addr = (int*)mlx_get_data_addr(m->xpm.xpm_block, &(m->xpm.xpm_b_b), &(m->xpm.xpm_b_s), &(m->xpm.xpm_b_e));
	m->xpm.xpm_ceiling = mlx_xpm_file_to_image(m->mlx_ptr, "./xpm/wood.xpm", &(m->xpm.xpm_c_x), &(m->xpm.xpm_c_y));
	m->xpm.xpm_c_addr = (int*)mlx_get_data_addr(m->xpm.xpm_ceiling, &(m->xpm.xpm_c_b), &(m->xpm.xpm_c_s), &(m->xpm.xpm_c_e));
}

void	init_env(t_env *m)
{
	int		i;

	m->ray.posX = 10;
	m->ray.posY = 10;
	m->ray.dirX = -1;
	m->ray.dirY = 0;
	m->ray.planeX = 0;
	m->ray.planeY = 0.66;
	i = -1;
	while (++i < 4)
		m->texture[i] = malloc(4 * (TEXTHT * TEXTWD));
}

void	init_texture(t_env *m)
{
	int		x;
	int		y;

	y = -1;
	while (++y < TEXTHT)
	{
		x = -1;
		while (++x < TEXTWD)
		{
			m->texture[0][TEXTWD * y + x] = m->xpm.xpm_f_addr[TEXTWD * y + x];
			m->texture[1][TEXTWD * y + x] = m->xpm.xpm_w_addr[TEXTWD * y + x];
			m->texture[2][TEXTWD * y + x] = m->xpm.xpm_b_addr[TEXTWD * y + x];;
			m->texture[3][TEXTWD * y + x] = m->xpm.xpm_c_addr[TEXTWD * y + x];;
		}
	}
}
