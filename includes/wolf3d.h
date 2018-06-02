/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksonu <ksonu@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 17:16:35 by ksonu             #+#    #+#             */
/*   Updated: 2018/06/01 22:31:10 by ksonu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF3D_H
# define WOLF3D_H
# include "../libs/libft/includes/libft.h"
# include "../libs/mlx/mlx.h"
# include <math.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# define WINDOW 1000
# define TEXTWD 64
# define TEXTHT 64
//# define MAPWD 24
//# define MAPHT 24

typedef struct	s_ray
{
	double		posX;
	double		posY;
	double		dirX;
	double		dirY;
	double		planeX;
	double		planeY;
	double		raydirX;
	double		raydirY;
	int			mapX;
	int			mapY;
	double		cameraX;
	double		deltadistX;
	double		deltadistY;
	double		sidedistX;
	double		sidedistY;
	int			stepX;
	int			stepY;
	double		perpwalldist;
	double		wallX;
	int			lineheight;
	int			side;
}				t_ray;

typedef struct	s_map
{
	int			**map;
	int			row;
	int			col;
}				t_map;

typedef struct	s_env
{
	t_ray		ray;
	t_map		map;
	void		*mlx_ptr;
	void		*win_ptr;
	void		*image;
	int			*data;
	int			bbp;
	int			size;
	int			endian;
	int			*texture[8];
	int			xorcolor;
	int			ycolor;
	int			xycolor;
}				t_env;

/*
** main.c
*/

/*
** init.c
*/
void			init_mlx(t_env *m);
void			init_env(t_env *m);
void			init_texture(t_env *m);

/* 
**map.c
*/
void			map_malloc(t_env *m);
void			map_read(t_env *m, char *av);
void			map_size(t_env *m, char *av);

/*
** wolf.c
*/
void			plot(t_env *m, int x, int start, int end);
void			wolf(t_env *m, t_ray *r);
void			raycasting(t_env *m, t_ray *r);
#endif
