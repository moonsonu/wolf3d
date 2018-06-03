/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksonu <ksonu@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 17:20:10 by ksonu             #+#    #+#             */
/*   Updated: 2018/06/02 15:55:07 by ksonu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		main(int ac, char **av)
{
	t_env	m;
	t_ray	r;

	ft_bzero(&m, sizeof(m));
	ft_bzero(&r, sizeof(r));
	if (ac == 2)
	{
		map_size(&m, av[1]);
		map_read(&m, av[1]);
		m.mlx_ptr = mlx_init();
		m.win_ptr = mlx_new_window(m.mlx_ptr, WINDOW, WINDOW, "WOLF");
		init_mlx(&m);
		init_env(&m);
		init_texture(&m);
		raycasting(&m);
		mlx_put_image_to_window(m.mlx_ptr, m.win_ptr, m.image, 0, 0);
		mlx_hook(m.win_ptr, 2, 0, keyfunction, &m);
		//mlx_hook(m->win_ptr, 17, 0, keyfunctions, m);
		mlx_loop(m.mlx_ptr);
	}
	return (0);
}
