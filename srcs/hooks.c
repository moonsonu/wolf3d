#include "wolf3d.h"

void	key_move(int key, t_env *m)
{
	double	tmpdirX;
	double	tmpplaneX;

	if (key == 124)
	{
		tmpdirX = m->ray.dirX;
		m->ray.dirX = tmpdirX * cos(-0.1) - m->ray.dirY * sin(-0.1);
		m->ray.dirY = tmpdirX * sin(-0.1) + m->ray.dirY * cos(-0.1);
		tmpplaneX = m->ray.planeX;
		m->ray.planeX = tmpplaneX * cos(-0.1) - m->ray.planeY * sin(-0.1);
		m->ray.planeY = tmpplaneX * sin(-0.1) + m->ray.planeY * cos(-0.1);
	}
	if (key == 123)
	{
		tmpdirX = m->ray.dirX;
		m->ray.dirX = tmpdirX * cos(0.1) - m->ray.dirY * sin(0.1);
		m->ray.dirY = tmpdirX * sin(0.1) + m->ray.dirY * cos(0.1);
		tmpplaneX = m->ray.planeX;
		m->ray.planeX = tmpplaneX * cos(0.1) - m->ray.planeY * sin(0.1);
		m->ray.planeY = tmpplaneX * sin(0.1) + m->ray.planeY * cos(0.1);
	}
	if (key == 126)
	{
		if (!m->map.map[(int)(m->ray.posX + m->ray.dirX * 0.1)][(int)m->ray.posY])
			m->ray.posX += m->ray.dirX * 0.1;
		if (!m->map.map[(int)m->ray.posX][(int)(m->ray.posY + m->ray.dirY * 0.1)])
			m->ray.posY += m->ray.dirY * 0.1;
	}
	if (key == 125)
	{
		if (!m->map.map[(int)(m->ray.posX - m->ray.dirX * 0.1)][(int)m->ray.posY])
			m->ray.posX -= m->ray.dirX * 0.1;
		if (!m->map.map[(int)m->ray.posX][(int)(m->ray.posY - m->ray.dirY * 0.1)])
			m->ray.posY -= m->ray.dirY * 0.1;
	}
}

int		keyfunction(int key, t_env *m)
{
	key == 53 ? exit(0) : 0;
	(key >= 123 && key <= 126) ? key_move(key, m) : 0;
	mlx_destroy_image(m->mlx_ptr, m->win_ptr);
	init_mlx(m);
	raycasting(m);
	return (0);
}
