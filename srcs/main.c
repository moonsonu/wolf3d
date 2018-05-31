/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksonu <ksonu@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 17:20:10 by ksonu             #+#    #+#             */
/*   Updated: 2018/05/30 16:26:30 by ksonu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d"

void	init_mlx(t_env *m)
{
	m->mlx_ptr = mlx_init();
	m->win_ptr = mlx_new_window(m->mlx_ptr, WIN, WIN, "WOLF3D - ksonu");
	m->image = mlx_new_image(m->mlx_ptr, WIN, WIN);
	m->data = (int*)mlx_get_data_addr(m->image, &m->bbp, &m->size, &m->endian);
}

int		main(int ac, char **av)
{
	t_env	m;

	ft_bzero(&m, sizeof(m));
	init_mlx(&m);
	init_env(&m);
}
