/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksonu <ksonu@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 17:16:35 by ksonu             #+#    #+#             */
/*   Updated: 2018/05/31 20:19:29 by ksonu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include "../libs/libft/includes/libft.h"
# include "../libs/mlx/mlx.h"
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# define WIN 1000

typedef struct	s_map
{
	int			**map;
	int			row;
	int			col;
}				t_map;

typedef struct	s_env
{
	t_map		map;
	void		*mlx_ptr;
	void		*win_ptr;
	void		*image;
	int			*data;
	int			bbp;
	int			size;
	int			endian;
}				t_env;

#endif
