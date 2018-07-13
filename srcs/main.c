/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksonu <ksonu@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 17:20:10 by ksonu             #+#    #+#             */
/*   Updated: 2018/07/12 17:29:10 by ksonu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	help_msg(void)
{
	ft_putendl("usage : ./wolf3d <map_file>");
	ft_putendl("Map has to be square and at lease 3x3\n");
}

int		error(int e)
{
	if (e == 0)
		return (0);
	if (e == 1)
		ft_putendl("usage: ./wolf3d <map_file>");
	if (e == 2)
		ft_putendl("error: invalid map");
	exit(0);
}

int		main(int ac, char **av)
{
	t_env	m;
	t_ray	r;

	ft_bzero(&m, sizeof(m));
	ft_bzero(&r, sizeof(r));
	if (ac != 2)
		error(1);
	help_msg();
	map_size(&m, av[1]);
	map_read(&m, av[1]);
	init_mlx(&m);
	init_env(&m);
	init_texture(&m);
	raycasting(&m);
	mlx_hook(m.win_ptr, 2, 0, keyfunction, &m);
	mlx_hook(m.win_ptr, 17, 0, key_exit, &m);
	mlx_put_image_to_window(m.mlx_ptr, m.win_ptr, m.image, 0, 0);
	plot_car(&m);
	mlx_loop(m.mlx_ptr);
	return (0);
}
