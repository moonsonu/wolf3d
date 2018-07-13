/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksonu <ksonu@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 17:16:35 by ksonu             #+#    #+#             */
/*   Updated: 2018/07/12 11:50:06 by ksonu            ###   ########.fr       */
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

typedef struct	s_xpm
{
	void		*xpm_floor;
	int			xpm_f_x;
	int			xpm_f_y;
	int			*xpm_f_addr;
	int			xpm_f_b;
	int			xpm_f_s;
	int			xpm_f_e;
	void		*xpm_wall;
	int			xpm_w_x;
	int			xpm_w_y;
	int			*xpm_w_addr;
	int			xpm_w_b;
	int			xpm_w_s;
	int			xpm_w_e;
	void		*xpm_block;
	int			xpm_b_x;
	int			xpm_b_y;
	int			*xpm_b_addr;
	int			xpm_b_b;
	int			xpm_b_s;
	int			xpm_b_e;
	void		*xpm_ceiling;
	int			xpm_c_x;
	int			xpm_c_y;
	int			*xpm_c_addr;
	int			xpm_c_b;
	int			xpm_c_s;
	int			xpm_c_e;
	void		*xpm_hand;
	int			xpm_h_x;
	int			xpm_h_y;
	int			*xpm_h_addr;
	int			xpm_h_b;
	int			xpm_h_s;
	int			xpm_h_e;
}				t_xpm;

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
	int			hit;
	double		floorX;
	double		floorY;
	double		distwall;
	double		distpos;
	double		distcurr;
	double		weight;
	double		currfloorX;
	double		currfloorY;
	int			floortextX;
	int			floortextY;
	int			texX;
	int			texY;
	int			color;
	int			start;
	int			end;
	int			d;
	int			textnum;
	double		movespeed;
	double		rotspeed;
}				t_ray;

typedef struct	s_map
{
	int			type;
}				t_map;

typedef struct	s_sprite
{
	double		x;
	double		y;
	int			texture;
}				t_sprite;

typedef struct	s_p_spt
{
	int			*spriteorder;
	double		*spritedistance;
	int			numsprites;
	double		invdet;
	double		transformX;
	double		transformY;
	int			spritescreenX;
	int			vmovescreen;
	int			spriteheight;
	int			drawstartX;
	int			drawstartY;
	int			drawendX;
	int			drawendY;
	int			spritewidth;
	int			s_texX;
	int			s_texY;
	int			s_d;
	double		spriteX;
	double		spriteY;
}				t_p_spt;

typedef struct	s_env
{
	t_ray		ray;
	t_xpm		xpm;
	t_map		**map;
//	t_sprite	*sprite;
//	t_p_spt		spt;
	void		*mlx_ptr;
	void		*win_ptr;
	void		*image;
	int			*data;
	int			bbp;
	int			size;
	int			endian;
	int			*texture[5];
	int			map_maxx;
	int			map_maxy;
}				t_env;

/*
** main.c
*/
int			error(int e);

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
void			ray_prep(t_env *m, int x);
void			ray_dda(t_env *m);
void			ray_wall(t_env *m);
void			ray_floor(t_env *m);
void			raycasting(t_env *m);

/*
** plot.c
*/
void			plot_car(t_env *m);
void			plot_floor(t_env *m, int x);
void			plot_sky(t_env *m, int x);
void			plot_wall(t_env *m, int x);

/*
** hooks.c
*/

void			key_leftright(int key, t_env *m);
void			key_updown(int key, t_env *m);
int				key_exit(t_env *m);
int				keyfunction(int key, t_env *m);
#endif
