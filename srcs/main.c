/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksonu <ksonu@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 17:20:10 by ksonu             #+#    #+#             */
/*   Updated: 2018/06/01 19:32:46 by ksonu            ###   ########.fr       */
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
		init_mlx(&m);
		init_env(&m);
		init_texture(&m);
		raycasting(&m, &r);
		mlx_put_image_to_window(m.mlx_ptr, m.win_ptr, m.image, 0, 0);
		mlx_loop(m.mlx_ptr);
	}
	return (0);
}
