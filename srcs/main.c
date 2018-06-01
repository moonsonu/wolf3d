/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksonu <ksonu@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 17:20:10 by ksonu             #+#    #+#             */
/*   Updated: 2018/05/31 21:18:17 by ksonu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"
#include <stdio.h>

void	map_malloc(t_env *m)
{
	int		i;

	i = -1;
	m->map.map = ft_memalloc(sizeof(int*) * (m->map.row + 1));
	while (++i < m->map.row)
		m->map.map[i] = malloc(sizeof(int) * (m->map.col + 1));
}

void	map_read(t_env *m, char *av)
{
	int		i;
	int		j;
	int		fd;
	char	**split;
	char	*line;

	i = -1;
	fd = open(av, O_RDONLY);
	while (++i < m->map.col + 1)
	{
		while (get_next_line(fd, &line) > 0)
		{
			split = ft_strsplit(line, ' ');
			j = -1;
			if (split
			while (++j < m->map.row && split[j])
			{
				printf("6\n");
				m->map.map[i][j] = ft_atoi(split[j]);
				printf("map[%d][%d] = [%d]\n", i, j, m->map.map[i][j]);
			}
			printf("7\n");
			ft_splitdel(split);
			ft_strdel(&line);
		}
	}
}

void	map_size(t_env *m, char *av)
{
	int		fd;
	int		i;
	char	*line;
	char	**split;

	i = -1;
	fd = open(av, O_RDONLY);
	map_malloc(m);
	while (get_next_line(fd, &line) > 0)
	{
		split = ft_strsplit(line, ' ');
		if (split && split[1] && !split[2] &&ft_atoi(split[0]) >= 2 && ft_atoi(split[1]) >= 2)
		{
			m->map.row = ft_atoi(split[0]);
			m->map.col = ft_atoi(split[1]);
			printf("row[%d] col[%d]\n", m->map.row, m->map.col);
		}
		ft_splitdel(split);
		ft_strdel(&line);
	}
	close(fd);
}

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
	if (ac == 2)
	{
		map_size(&m, av[1]);
		map_read(&m, av[1]);
		init_mlx(&m);
	}
	return (0);
	//init_env(&m);
}
