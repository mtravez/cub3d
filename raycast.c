#include "cub3d.h"

static char map[8][8] = {
	{'1','1','1','1','1','1','1','1'},
	{'1','0','0','0','0','0','0','1'},
	{'1','0','1','0','0','0','0','1'},
	{'1','1','1','0','0','0','0','1'},
	{'1','0','0','0','0','0','0','1'},
	{'1','0','0','0','0','1','0','1'},
	{'1','0','1','0','0','1','0','1'},
	{'1','1','1','1','1','1','1','1'}
};

float	dist(float ax, float ay, float bx, float by, float ang)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)) + ang - ang);
}

void	draw_rays_3d(t_player player, mlx_image_t *crash, t_map3d *map3d)
{
	t_ray ray;
	float	aTan;
	float	nTan;
	int32_t	color;

	color = PINK;
	ray.ra = player.pa - DR * 30;
	if (ray.ra < 0)
		ray.ra += 2 * PI;
	if (ray.ra > 2 * PI)
		ray.ra -= 2 * PI;
	ray.r = 0;
	while (ray.r < RAYNR)
	{
		//---HORIZONTAL WALLS---
		ray.dof = 0;
		ray.disH = 10000000;
		ray.hx = player.px;
		ray.hy = player.py;
		aTan = -1 / tan(ray.ra);
		if (ray.ra > PI)
		{
			ray.ry = (((int) player.py >> 6) << 6) - 0.0001;
			ray.rx = (player.py - ray.ry) * aTan + player.px;
			ray.yo = -64;
			ray.xo = -ray.yo * aTan;
		}
		if (ray.ra < PI)
		{
			ray.ry = (((int) player.py >> 6) << 6) + 64;
			ray.rx = (player.py - ray.ry) * aTan + player.px;
			ray.yo = 64;
			ray.xo = -ray.yo * aTan;
		}
		while (ray.dof < 8)
		{
			ray.mx = (int) (ray.rx) >> 6;
			ray.my = (int) (ray.ry) >> 6;
			if (ray.mx >= 0 && ray.my >= 0 && ray.mx < MAPX && ray.my < MAPY && map[ray.my][ray.mx] == '1')
			{
				ray.hx = ray.rx;
				ray.hy = ray.ry;
				ray.disH = dist(player.px, player.py, ray.hx, ray.hy, ray.ra);
				ray.dof = 8;
			}
			else
			{
				ray.rx += ray.xo;
				ray.ry += ray.yo;
				ray.dof += 1;
			}
		}
	
		//---VERTICAL WALLS---
		ray.dof = 0;
		ray.disV = 10000000;
		ray.vx = player.px;
		ray.vy = player.py;
		nTan = -tan(ray.ra);
		if (ray.ra > PI2 && ray.ra < PI3)
		{
			ray.rx = (((int) player.px >> 6) << 6) - 0.0001;
			ray.ry = (player.px - ray.rx) * nTan + player.py;
			ray.xo = -64;
			ray.yo = -ray.xo * nTan;
		}
		if (ray.ra < PI2 || ray.ra > PI3)
		{
			ray.rx = (((int) player.px >> 6) << 6) + 64;
			ray.ry = (player.px - ray.rx) * nTan + player.py;
			ray.xo = 64;
			ray.yo = -ray.xo * nTan;
		}
		while (ray.dof < 8)
		{
			ray.mx = (int) (ray.rx) >> 6;
			ray.my = (int) (ray.ry) >> 6;
			if (ray.mx >= 0 && ray.my >= 0 && ray.mx < MAPX && ray.my < MAPY && map[ray.my][ray.mx] == '1')
			{
				ray.vx = ray.rx;
				ray.vy = ray.ry;
				ray.disV = dist(player.px, player.py, ray.vx, ray.vy, ray.ra);
				ray.dof = 8;
			}
			else
			{
				ray.rx += ray.xo;
				ray.ry += ray.yo;
				ray.dof += 1;
			}
		}
		if (ray.disH < ray.disV)
		{
			ray.rx = ray.hx;
			ray.ry = ray.hy;
			ray.dist = ray.disH;
			color = SHADOW;
		}
		else
		{
			ray.rx = ray.vx;
			ray.ry = ray.vy;
			ray.dist = ray.disV;
			color = PINK;
		}
		crash->instances[ray.r].x = ray.rx;
		crash->instances[ray.r].y = ray.ry;
		ray.ra += DR;
		if (ray.ra < 0)
			ray.ra += 2 * PI;
		if (ray.ra > 2 * PI)
			ray.ra -= 2 * PI;
		
		//---DRAW 3D WALLS---
		float ca = player.pa - ray.ra;
		if (ca < 0)
			ca += 2 * PI;
		if (ca > 2 * PI)
			ca -= 2 * PI;
		ray.dist *= cos(ca);
		float lineH = (MAPS * 420) / ray.dist;
		if (lineH > 420)
			lineH = 420;
		float lineO = 250 - lineH / 2;
		if (map3d->map_3d[ray.r])
			mlx_delete_image(player.mlx, map3d->map_3d[ray.r]);
		map3d->map_3d[ray.r] = mlx_new_image(player.mlx, 8, lineH * 8);
		paint_image(map3d->map_3d[ray.r], color);
		mlx_image_to_window(player.mlx, map3d->map_3d[ray.r], (ray.r * 8 + 530) - ray.r, lineO);
		ray.r++;
	}
}

