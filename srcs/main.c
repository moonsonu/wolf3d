/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksonu <ksonu@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 17:20:10 by ksonu             #+#    #+#             */
/*   Updated: 2018/05/31 21:58:40 by ksonu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

int		main(int ac, char **av)
{
	t_env	m;

	ft_bzero(&m, sizeof(m));
	if (ac == 2)
	{
		map_size(&m, av[1]);
		map_read(&m, av[1]);
		init_mlx(&m);
		init_env(&m);
	}
	return (0);
	//init_env(&m);
}
