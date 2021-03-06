/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksonu <ksonu@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/29 17:16:35 by ksonu             #+#    #+#             */
/*   Updated: 2018/07/31 18:29:47 by ksonu            ###   ########.fr       */
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
	void		*xpm_intro;
	int			xpm_i_x;
	int			xpm_i_y;
	int			*xpm_i_addr;
	int			xpm_i_b;
	int			xpm_i_s;
	int			xpm_i_e;
	void		*xpm_sprite;
	int			xpm_s_x;
	int			xpm_s_y;
	int			*xpm_s_addr;
	int			xpm_s_b;
	int			xpm_s_s;
	int			xpm_s_e;
}				t_xpm;

typedef struct	s_ray
{
	double		posx;
	double		posy;
	double		dirx;
	double		diry;
	double		planex;
	double		planey;
	double		raydirx;
	double		raydiry;
	int			mapx;
	int			mapy;
	double		camerax;
	double		deltadistx;
	double		deltadisty;
	double		sidedistx;
	double		sidedisty;
	int			stepx;
	int			stepy;
	double		perpwalldist;
	double		wallx;
	int			lineheight;
	int			side;
	int			hit;
	double		floorx;
	double		floory;
	double		distwall;
	double		distpos;
	double		distcurr;
	double		weight;
	double		currfloorx;
	double		currfloory;
	int			floortextx;
	int			floortexty;
	int			texx;
	int			texy;
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

typedef struct	s_env
{
	t_ray		ray;
	t_xpm		xpm;
	t_map		**map;
	int			color;
	void		*mlx_ptr;
	void		*win_ptr;
	void		*image;
	int			*data;
	int			bbp;
	int			size;
	int			endian;
	int			*texture[7];
	int			map_maxx;
	int			map_maxy;
}				t_env;

/*
** main.c
*/
void			intro(t_env *m);
int				keyfunction(int key, t_env *m);
void			help_msg(void);
int				error(int e);

/*
** init.c
*/
void			init_mlx(t_env *m);
void			init_mlx_2(t_env *m);
void			init_env(t_env *m);
void			init_texture(t_env *m);
void			init_texture_2(t_env *m);

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

void			key_right(int key, t_env *m);
void			key_left(int key, t_env *m);
void			key_speed(int key, t_env *m);
void			key_updown(int key, t_env *m);
int				key_exit(t_env *m);

/*
** minimap.c
*/

void			plot_mm(t_env *m, int x, int s, int e);
void			plot_square(t_env *m, int x, int y);
void			plot_dot(t_env *m);
void			minimap(t_env *m);
#endif
