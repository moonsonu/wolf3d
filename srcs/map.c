/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksonu <ksonu@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 21:57:47 by ksonu             #+#    #+#             */
/*   Updated: 2018/06/05 21:57:03 by ksonu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

void	map_malloc(t_env *m)
{
	int		i;

	i = -1;
	m->map = ft_memalloc(sizeof(int*) * (m->map_maxx + 1));
	while (++i < m->map_maxx)
		m->map[i] = malloc(sizeof(int) * (m->map_maxy + 1));
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
	map_malloc(m);
	while (++i < m->map_maxy + 1)
	{
		if (get_next_line(fd, &line) == 1)
		{
			split = ft_strsplit(line, ' ');
			j = -1;
			while (++j < m->map_maxx + 1 && split[j])
				m->map[i][j].type = ft_atoi(split[j]);
			ft_splitdel(split);
			ft_strdel(&line);
		}
	}
	close(fd);
}

void	map_size(t_env *m, char *av)
{
	int		fd;
	int		i;
	char	*line;

	i = -1;
	fd = open(av, O_RDONLY);
	m->map_maxx = 0;
	m->map_maxy = 0;
	while (get_next_line(fd, &line) > 0)
	{
		(m->map_maxy)++;
		m->map_maxx= ft_wdcount(line, ' ') + 1;
		ft_strdel(&line);
	}
	close(fd);
}
