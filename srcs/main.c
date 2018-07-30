/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksonu <ksonu@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 17:20:10 by ksonu             #+#    #+#             */
/*   Updated: 2018/07/29 18:07:10 by ksonu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	intro(t_env *m)
{
	t_env	intro;
	int		x;
	int		y;
	int		i;

	i = 0;
	y = -1;
	mlx_hook(m->win_ptr, 2, 0, keyfunction, m);
	mlx_hook(m->win_ptr, 17, 0, key_exit, m);
	intro.image = mlx_new_image(m->mlx_ptr, (m->xpm.xpm_i_x), (m->xpm.xpm_i_y));
	intro.data = (int*)mlx_get_data_addr(intro.image, &m->bbp,
			&m->size, &m->endian);
	while (++y < m->xpm.xpm_i_y)
	{
		x = -1;
		while (++x < m->xpm.xpm_i_x)
			intro.data[(y * m->xpm.xpm_i_x) + x] = m->texture[5][i++];
	}
	mlx_put_image_to_window(m->mlx_ptr, m->win_ptr, intro.image, 0, 0);
	mlx_string_put(m->mlx_ptr, m->win_ptr, 500, 500, 0xFFFFFF,
			"PRESS ANY KEY TO START");
	mlx_loop(m->mlx_ptr);
}

int		keyfunction(int key, t_env *m)
{
	ft_bzero(m->data, WINDOW * WINDOW * 4);
	key == 53 ? exit(0) : 0;
	(key == 123) ? key_left(key, m) : 0;
	(key == 124) ? key_right(key, m) : 0;
	(key == 125 || key == 126 || key == 1) ? key_updown(key, m) : 0;
	(key == 1) ? key_speed(key, m) : 0;
	raycasting(m);
	mlx_put_image_to_window(m->mlx_ptr, m->win_ptr, m->image, 0, 0);
	plot_car(m);
	return (0);
}

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
	t_env		m;
	t_ray		r;
	t_sprite	s;

	ft_bzero(&m, sizeof(m));
	ft_bzero(&r, sizeof(r));
	ft_bzero(&s, sizeof(s));
	if (ac != 2)
		error(1);
	help_msg();
	system("afplay ./xpm/bb.mp3 &");
	map_size(&m, av[1]);
	map_read(&m, av[1]);
	init_mlx(&m);
	init_env(&m);
	init_texture(&m);
	intro(&m);
	raycasting(&m);
	mlx_put_image_to_window(m.mlx_ptr, m.win_ptr, m.image, 0, 0);
	plot_car(&m);
	mlx_loop(m.mlx_ptr);
	return (0);
}
