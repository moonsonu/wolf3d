/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksonu <ksonu@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/31 21:57:47 by ksonu             #+#    #+#             */
/*   Updated: 2018/06/05 17:21:17 by ksonu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf3d.h"

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
	map_malloc(m);
	while (++i < m->map.col + 1)
	{
		if (get_next_line(fd, &line) == 1)
		{
			split = ft_strsplit(line, ' ');
			j = -1;
			while (++j < m->map.row + 1 && split[j])
				m->map.map[i][j] = ft_atoi(split[j]);
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
	m->map.row = 0;
	m->map.col = 0;
	while (get_next_line(fd, &line) > 0)
	{
		(m->map.col)++;
		m->map.row = ft_wdcount(line, ' ') + 1;
		ft_strdel(&line);
	}
	close(fd);
}
