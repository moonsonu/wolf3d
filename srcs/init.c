/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksonu <ksonu@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 21:58:17 by ksonu             #+#    #+#             */
/*   Updated: 2018/06/08 21:13:51 by ksonu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	hand(t_env *m)
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
void	init_mlx(t_env *m)
{
	//m->mlx_ptr = mlx_init();
	//m->win_ptr = mlx_new_window(m->mlx_ptr, WINDOW, WINDOW, "WOLF");
	m->image = mlx_new_image(m->mlx_ptr, WINDOW, WINDOW);
	m->data = (int*)mlx_get_data_addr(m->image, &m->bbp, &m->size, &m->endian);
	m->xpm.xpm_floor = mlx_xpm_file_to_image(m->mlx_ptr, "./xpm/ground.xpm", &(m->xpm.xpm_f_x), &(m->xpm.xpm_f_y));
	m->xpm.xpm_f_addr = (int*)mlx_get_data_addr(m->xpm.xpm_floor, &(m->xpm.xpm_f_b), &(m->xpm.xpm_f_s), &(m->xpm.xpm_f_e));
	m->xpm.xpm_wall = mlx_xpm_file_to_image(m->mlx_ptr, "./xpm/brick.xpm", &(m->xpm.xpm_w_x), &(m->xpm.xpm_w_y));
	m->xpm.xpm_w_addr = (int*)mlx_get_data_addr(m->xpm.xpm_wall, &(m->xpm.xpm_w_b), &(m->xpm.xpm_w_s), &(m->xpm.xpm_w_e));
	m->xpm.xpm_block = mlx_xpm_file_to_image(m->mlx_ptr, "./xpm/question.xpm", &(m->xpm.xpm_b_x), &(m->xpm.xpm_b_y));
	m->xpm.xpm_b_addr = (int*)mlx_get_data_addr(m->xpm.xpm_block, &(m->xpm.xpm_b_b), &(m->xpm.xpm_b_s), &(m->xpm.xpm_b_e));
	m->xpm.xpm_ceiling = mlx_xpm_file_to_image(m->mlx_ptr, "./xpm/sky.xpm", &(m->xpm.xpm_c_x), &(m->xpm.xpm_c_y));
	m->xpm.xpm_c_addr = (int*)mlx_get_data_addr(m->xpm.xpm_ceiling, &(m->xpm.xpm_c_b), &(m->xpm.xpm_c_s), &(m->xpm.xpm_c_e));
	m->xpm.xpm_hand = mlx_xpm_file_to_image(m->mlx_ptr, "./xpm/car.xpm", &(m->xpm.xpm_h_x), &(m->xpm.xpm_h_y));
	m->xpm.xpm_h_addr = (int*)mlx_get_data_addr(m->xpm.xpm_hand, &(m->xpm.xpm_h_b), &(m->xpm.xpm_h_s), &(m->xpm.xpm_h_e));
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
	m->ray.movespeed = 0.1;
	m->ray.rotspeed = 0.1;
	i = -1;
	while (++i < 4)
		m->texture[i] = malloc(4 * (TEXTHT * TEXTWD));
	m->texture[4] = malloc(4 * (m->xpm.xpm_h_x * m->xpm.xpm_h_y));
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
			m->texture[2][TEXTWD * y + x] = m->xpm.xpm_b_addr[TEXTWD * y + x];
			m->texture[3][TEXTWD * y + x] = m->xpm.xpm_c_addr[TEXTWD * y + x];
		}
	}
	y = -1;
	while (++y < m->xpm.xpm_h_y)
	{
		x = -1;
		while (++x < m->xpm.xpm_h_x)
			m->texture[4][m->xpm.xpm_h_x * y + x] = m->xpm.xpm_h_addr[m->xpm.xpm_h_x * y + x];
	}
}
