#include "cub3d.h"

static char map[10][10] = {
	{'1','1','1','1','1','1','1','1','1','1'},
	{'1','0','0','0','0','0','0','0','0','1'},
	{'1','0','1','0','0','0','0','0','0','1'},
	{'1','1','1','0','0','0','0','0','0','1'},
	{'1','0','0','0','0','0','0','0','0','1'},
	{'1','0','0','0','0','1','0','0','0','1'},
	{'1','0','1','0','0','1','0','0','0','1'},
	{'1','1','1','1','1','1','1','1','1','1'}
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

uint32_t	get_texcolor(mlx_texture_t *t, uint32_t x, uint32_t y)
{
	uint32_t	color;

	color = t->pixels[t->height * y * BPP + x * BPP] << 24 | \
	t->pixels[t->height * y * BPP + x * BPP + 1] << 16 | \
	t->pixels[t->height * y * BPP + x * BPP + 2] << 8 | \
	t->pixels[t->height * y * BPP + x * BPP + 3];
	// color = t->pixels[t->height * y + x * BPP] << 24;
	// color += t->pixels[t->height * y + x * BPP + 1] << 16;
	// printf("%X\n", color);
	return (color);
}

// uint32_t	get_texcolor(mlx_texture_t *t, uint32_t x, uint32_t y, float shade)
// {
// 	uint32_t	color;

// 	color = (int)(t->pixels[t->height * y * BPP + x * BPP] * shade) << 24 | \
// 	(int)(t->pixels[t->height * y * BPP + x * BPP + 1] * shade) << 16 | \
// 	(int)(t->pixels[t->height * y * BPP + x * BPP + 2] * shade) << 8 | \
// 	t->pixels[t->height * y * BPP + x * BPP + 3];
// 	return (color);
// }

void	set_tex_values(t_ray ray, t_player player, t_texture *t)
{
	t->lineH = (WIN_H * 64) / ray.dist;
	t->t = player.textures[ray.wall];
	t->ty_step = 1.0 * t->t->height / t->lineH;
	t->ty_off = 0;
	if (t->lineH > WIN_H)
	{
		t->ty_off = (t->lineH - WIN_H) / 2.0;
		t->lineH = WIN_H;
	}
	t->lineO = (WIN_H / 2) - (t->lineH / 2);
	t->ty = t->ty_off * t->ty_step;
	if (ray.disV > ray.disH)
	{
		t->tx = (int)(ray.rx) % t->t->width;
		if (ray.ra > PI)
			t->tx = t->t->width - 1 - t->tx;
	}
	else
	{
		t->tx = (int) (ray.ry) % t->t->height;
		if (ray.ra > PI2 && ray.ra < PI3)
			t->tx = t->t->height - 1 - t->tx;
	}
}

void	draw_texture(t_ray ray, t_player player, int32_t color)
{
	t_texture	t;
	int	i;

	set_tex_values(ray, player, &t);
	i = 0;
	while (i < t.lineH)
	{
		color = get_texcolor(t.t, (int) t.tx, (int)t.ty);
		player.map3d->buffer[(int)(i + t.lineO)][ray.r] = color;
		t.ty += t.ty_step;
		i++;
	}
	i = 0;
	while (i < WIN_H)
	{
		if (i <= t.lineO)
			color = CEILING;
		if (i >= t.lineH + t.lineO)
			color = FLOOR;
		if (i < t.lineO || i > t.lineH + t.lineO)
			player.map3d->buffer[i][ray.r] = color;
		i++;
	}
}

void	start_ray(t_ray *ray, t_player player)
{
	ray->dof = 0;
	ray->disH = 10000000;
	ray->hx = player.px;
	ray->hy = player.py;
	// ray->dof = 0;
	ray->disV = 10000000;
	ray->vx = player.px;
	ray->vy = player.py;
}

void	draw_rays_3d(t_player player, mlx_image_t *crash)
{
	t_ray	ray;
	// float	aTan;
	float	nTan;
	float	ca;
	int32_t	color;

	color = PINK;
	ray.ra = player.pa - DR * 30;
	if (ray.ra < 0)
		ray.ra += 2 * PI;
	if (ray.ra > 2 * PI)
		ray.ra -= 2 * PI;
	ray.r = 0;
	clear_buffer(player.map3d);
	while (ray.r < RAYNR)
	{
		//---HORIZONTAL WALLS---
		start_ray(&ray, player);
		// aTan = -1 / tan(ray.ra);
		if (ray.ra > PI)
		{
			ray.ry = (((int) player.py >> 6) << 6) - 0.0001;
			ray.yo = -64;
		}
		if (ray.ra <= PI)
		{
			ray.ry = (((int) player.py >> 6) << 6) + 64;
			ray.yo = 64;
		}
		ray.rx = (player.py - ray.ry) * (-1 / tan(ray.ra)) + player.px;
		ray.xo = -ray.yo * (-1 / tan(ray.ra));
		while (ray.dof < 8)
		{
			ray.mx = (int) (ray.rx) >> 6;
			ray.my = (int) (ray.ry) >> 6;
			if (ray.mx >= 0 && ray.my >= 0 && ray.mx < MAPX && ray.my < MAPY && map[ray.my][ray.mx] == '1')
			{
				ray.hx = ray.rx;
				ray.hy = ray.ry;
				ray.disH = dist(player.px, player.py, ray.hx, ray.hy, ray.ra);
				break;
			}
			ray.rx += ray.xo;
			ray.ry += ray.yo;
			ray.dof += 1;
		}
	
		//---VERTICAL WALLS---
		ray.dof = 0;
		nTan = -tan(ray.ra);
		if (ray.ra > PI2 && ray.ra < PI3)
		{
			ray.rx = (((int) player.px >> 6) << 6) - 0.0001;
			ray.xo = -64;
		}
		if (ray.ra < PI2 || ray.ra > PI3)
		{
			ray.rx = (((int) player.px >> 6) << 6) + 64;
			ray.xo = 64;
		}
		ray.ry = (player.px - ray.rx) * nTan + player.py;
		ray.yo = -ray.xo * nTan;
		while (ray.dof < 8)
		{
			ray.mx = (int) (ray.rx) >> 6;
			ray.my = (int) (ray.ry) >> 6;
			if (ray.mx >= 0 && ray.my >= 0 && ray.mx < MAPX && ray.my < MAPY && map[ray.my][ray.mx] == '1')
			{
				ray.vx = ray.rx;
				ray.vy = ray.ry;
				ray.disV = dist(player.px, player.py, ray.vx, ray.vy, ray.ra);
				break;
			}
			ray.rx += ray.xo;
			ray.ry += ray.yo;
			ray.dof += 1;
		}
		if (ray.disH < ray.disV)
		{
			ray.rx = ray.hx;
			ray.ry = ray.hy;
			ray.dist = ray.disH;
			color = SHADOW;
			ray.shade = 0.8;
			if (ray.yo < 0)
				ray.wall = SOUTH;
			else
				ray.wall = NORTH;
		}
		else
		{
			ray.rx = ray.vx;
			ray.ry = ray.vy;
			ray.dist = ray.disV;
			color = PINK;
			ray.shade = 1;
			if (ray.xo < 0)
				ray.wall = WEST;
			else
				ray.wall = EAST;
		}
		ray.ra += DR / (WIN_W / 60);
		if (ray.ra < 0)
			ray.ra += 2 * PI;
		if (ray.ra > 2 * PI)
			ray.ra -= 2 * PI;
		paint_image(crash, 0xFF0000FF);
		
		//---DRAW 3D WALLS---
		ca = player.pa - ray.ra;
		if (ca < 0)
			ca += 2 * PI;
		if (ca > 2 * PI)
			ca -= 2 * PI;
		ray.dist *= cos(ca);
		draw_texture(ray, player, color);
		ray.r++;
	}
	paint_buffer(player);
}


