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

void	clear_buffer(t_map3d *map)
{
	u_int32_t	i;
	u_int32_t	j;

	i = 0;
	while (i < WIN_H)
	{
		j = 0;
		while (j < WIN_W)
		{
			map->buffer[i][j] = 0;
			j++;
		}
		i++;
	}
}

void	paint_buffer(t_player player)
{
	u_int32_t	i;
	u_int32_t	j;

	i = 0;
	while (i < WIN_H)
	{
		j = 0;
		while (j < WIN_W)
		{
			mlx_put_pixel(player.img, j, i, player.map3d->buffer[i][j]);
			j++;
		}
		i++;
	}
}

// uint32_t	get_texcolor(mlx_texture_t *t, uint32_t x, uint32_t y)
// {
// 	uint32_t	color;

// 	color = t->pixels[t->height * y * BPP + x * BPP] << 24 | \
// 	t->pixels[t->height * y * BPP + x * BPP + 1] << 16 | \
// 	t->pixels[t->height * y * BPP + x * BPP + 2] << 8 | \
// 	t->pixels[t->height * y * BPP + x * BPP + 3];
// 	// color = t->pixels[t->height * y + x * BPP] << 24;
// 	// color += t->pixels[t->height * y + x * BPP + 1] << 16;
// 	// printf("%X\n", color);
// 	return (color);
// }

uint32_t	get_texcolor(mlx_texture_t *t, uint32_t x, uint32_t y, float shade)
{
	uint32_t	color;

	color = (int)(t->pixels[t->height * y * BPP + x * BPP] * shade) << 24 | \
	(int)(t->pixels[t->height * y * BPP + x * BPP + 1] * shade) << 16 | \
	(int)(t->pixels[t->height * y * BPP + x * BPP + 2] * shade) << 8 | \
	t->pixels[t->height * y * BPP + x * BPP + 3];
	// color = t->pixels[t->height * y + x * BPP] << 24;
	// color += t->pixels[t->height * y + x * BPP + 1] << 16;
	// printf("%X\n", color);
	return (color);
}

// void	draw_texture(t_ray ray, t_player player, int32_t color)
// {
// 	mlx_texture_t *t = player.textures[0];
// 	float lineH = (MAPS * WIN_H) / ray.dist;
// 	if (lineH > WIN_H)
// 		lineH = WIN_H;
// 	float lineO = (WIN_H / 2) - lineH / 2;
// 	// if (player.map3d->map_3d[ray.r])
// 	// 	mlx_delete_image(player.mlx, player.map3d->map_3d[ray.r]);
// 	// player.map3d->map_3d[ray.r] = mlx_new_image(player.mlx, WIN_W / 57.0, lineH);
// 	// paint_image(player.img, color);
// 	// mlx_image_to_window(player.mlx, player.map3d->map_3d[ray.r], (ray.r * WIN_W * 0.018) - ray.r, lineO);
// 	// printf("%f\n", ray.rx);
// 	// if (player.img)
// 	// 	mlx_delete_image(player.mlx, player.img);
// 	// player.img = mlx_new_image(player.mlx, WIN_W, WIN_W);
// 	for (u_int32_t i = 0; i < lineH; i++)
// 	{
// 		u_int32_t j = 0;
// 		while (j < 13 && (ray.r * 13 + j) < WIN_W)
// 		{
// 			// mlx_put_pixel(player.img, (ray.r * 13) + j, i + lineO, color);
// 			player.map3d->buffer[(int)(i + lineO)][ray.r * 13 + j] = color;
// 			j++;
// 		}
// 	}
// }

void	draw_texture(t_ray ray, t_player player, int32_t color)
{
	mlx_texture_t *t = player.textures[ray.wall];
	int lineH = (WIN_H * MAPS) / ray.dist;
	float ty_step = 1.0 * t->height / lineH;
	float ty_off = 0;
	if (lineH > WIN_H)
	{
		ty_off = (lineH - WIN_H) / 2.0;
		lineH = WIN_H;
	}
	float lineO = (WIN_H / 2) - (lineH / 2);
	float ty = ty_off * ty_step;
	// float tx = (int) (ray.rx / 2.0) % t->width;
	float tx;
	if (ray.disV > ray.disH)
	{
		tx = (int)(ray.rx) % t->width;
		if (ray.ra > PI)
			tx = t->width - 1 - tx;
	}
	else
	{
		tx = (int) (ray.ry) % t->height;
		if (ray.ra > 0 && ray.ra < PI2)
			tx = t->height - 1 - tx;
	}
	for (int i = 0; i < lineH; i++)
	{
		color = get_texcolor(t, (int) tx, (int)ty, ray.shade);
		u_int32_t j = 0;
		while (j < 7 && (ray.r * 7 + j) < WIN_W)
		{
			// mlx_put_pixel(player.img, (ray.r * 13) + j, i + lineO, color);
			player.map3d->buffer[(int)(i + lineO)][ray.r * 7 + j] = color;
			j++;
		}
		ty += ty_step;
	}
}

void	draw_rays_3d(t_player player, mlx_image_t *crash)
{
	t_ray ray;
	float	aTan;
	float	nTan;
	int32_t	color;
	int		size;

	color = PINK;
	ray.ra = player.pa - DR * 30;
	if (ray.ra < 0)
		ray.ra += 2 * PI;
	if (ray.ra > 2 * PI)
		ray.ra -= 2 * PI;
	ray.r = 0;
	size = 0;
	clear_buffer(player.map3d);
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
			if (ray.ry < 0)
				ray.wall = SOUTH;
			else
				ray.wall = NORTH;
			ray.rx = ray.hx;
			ray.ry = ray.hy;
			ray.dist = ray.disH;
			color = SHADOW;
			ray.shade = 0.5;
			// if (ray.ra > 0 && ray.ra < PI2)
		}
		else
		{
			if (ray.rx < 0)
				ray.wall = WEST;
			else
				ray.wall = EAST;
			ray.rx = ray.vx;
			ray.ry = ray.vy;
			ray.dist = ray.disV;
			color = PINK;
			ray.shade = 1;
			// if (ray.ra > PI)
		}
		ray.ra += DR / 2;
		if (ray.ra < 0)
			ray.ra += 2 * PI;
		if (ray.ra > 2 * PI)
			ray.ra -= 2 * PI;
		// crash->instances[ray.r].x = ray.rx;
		// crash->instances[ray.r].y = ray.ry;
		paint_image(crash, 0xFF0000FF);
		
		//---DRAW 3D WALLS---
		float ca = player.pa - ray.ra;
		if (ca < 0)
			ca += 2 * PI;
		if (ca > 2 * PI)
			ca -= 2 * PI;
		ray.dist *= cos(ca);
		ray.wall = EAST;
		draw_texture(ray, player, color);
		// break;
		ray.r++;
	}
	paint_buffer(player);
}


