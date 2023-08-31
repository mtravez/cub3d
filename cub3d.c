/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:21:07 by mtravez           #+#    #+#             */
/*   Updated: 2023/08/31 16:02:52 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char map[10][10] = {
	{'1','1','1','1','1','1','1','1','1','1'},
	{'1','0','0','0','0','0','0','0','0','1'},
	{'1','0','1','0','0','0','0','0','0','1'},
	{'1','1','1','0','0','0','0','0','0','1'},
	{'1','0','0','0','0','0','0','0','0','1'},
	{'1','0','0','0','0','1','0','0','0','1'},
	{'1','0','1','0','0','1','0','0','0','1'},
	{'1','1','1','1','1','1','1','1','1','1'}
};

mlx_image_t *crash;

int get_rgba(int r, int g, int b, int a)
{
    return ((a << 24) | (r << 16) | (g << 8) | b);
}

void paint_player(mlx_image_t *img, int32_t color)
{
	u_int32_t i;
	u_int32_t j;
	
	i = 0;
	while (i < img->height)
	{
		j = 0;
		while (j < img->width)
		{
			mlx_put_pixel(img, i, j, color);
			j++;
		}
		i++;
	}
}

void paint_image(mlx_image_t *img, int32_t color)
{
	u_int32_t i;
	u_int32_t j;
	
	i = 0;
	while (i < img->height)
	{
		j = 0;
		while (j < img->width)
		{
			mlx_put_pixel(img, j, i, color);
			j++;
		}
		i++;
	}
}

// void	delete_map(mlx_t *mlx, t_map3d *map3d)
// {
// 	int	i;

// 	i = 0;
// 	while (i < RAYNR)
// 	{
// 		mlx_delete_image(mlx, map3d->map_3d[i]);
// 		i++;
// 	}
// }

void	draw_player(void *mlx, t_player *player)
{
	player->img = mlx_new_image(mlx, 10, 10);
	// ft_memset(player->img->pixels, get_rgba(245, 40, 145, 1), player->img->width * player->img->height * BPP);
	paint_image(player->img, 0xFAA0EFFF);
	
	player->dir = mlx_new_image(mlx, 4, 4);
	paint_image(player->dir, 0x0000FFFF);
	
	mlx_image_to_window(mlx, player->img, player->px, player->py);
	mlx_image_to_window(mlx, player->dir, player->img->instances[0].x + player->pdx * 5, player->img->instances[0].y + player->pdy * 5 + 10);
}

void	draw_map_2d(void *mlx)
{
	int x, y, x0, y0;
	
	mlx_image_t *square1 = mlx_new_image(mlx, MAPSIZE, MAPSIZE);
	paint_image(square1, WALL);
	
	mlx_image_t *square2 = mlx_new_image(mlx, MAPSIZE, MAPSIZE);
	paint_image(square2, GROUND);
	
	mlx_image_t **to_draw = &square1;
	for (y = 0; y < MAPY; y++)
	{
		for (x = 0; x < MAPX; x++)
		{
			if (map[y][x] == '1')
				to_draw = &square1;
			else
				to_draw = &square2;
			x0 = x * MAPSIZE;
			y0 = y * MAPSIZE;
			mlx_image_to_window(mlx, *to_draw, x0 + x, y0 + y);
		}
	}
}

void buttons(mlx_key_data_t key, void *param)
{
	t_player *player = param;

	if (key.key == MLX_KEY_LEFT && key.action != MLX_RELEASE)
	{
		player->pa -= 0.1;
		if (player->pa < 0)
			player->pa += 2 * PI;
		player->pdx = cos(player->pa) * 7;
		player->pdy = sin(player->pa) * 7;
	}
	if (key.key == MLX_KEY_RIGHT)
	{
		player->pa += 0.1;
		if (player->pa > 2 * PI)
			player->pa -= 2 * PI;
		player->pdx = cos(player->pa) * 7;
		player->pdy = sin(player->pa) * 7;
	}

	int xo;
	if (player->pdx < 0)
		xo = -20;
	else
		xo = 20;
	int	yo;
	if (player->pdy < 0)
		yo = -20;
	else
		yo = 20;
	int ipx = player->px / 64.0, ipx_add_xo = (player->px + xo) / 64.0, ipx_sub_xo = (player->px - xo) / 64.0;
	int ipy = player->py / 64.0, ipy_add_yo = (player->py + yo) / 64.0, ipy_sub_yo = (player->py - yo) / 64.0;
	
	if (key.key == MLX_KEY_W)
	{
		if (map[ipy][ipx_add_xo] == '0')
			player->px += player->pdx;
		if (map[ipy_add_yo][ipx] == '0')
			player->py += player->pdy;
	}
	if (key.key == MLX_KEY_S)
	{
		if (map[ipy][ipx_sub_xo] == '0')
			player->px -= player->pdx;
		if (map[ipy_sub_yo][ipx] == '0')
			player->py -= player->pdy;
	}
	if ((cos(player->pa + (PI / 2)) * 5) < 0)
		xo = -20;
	else
		xo = 20;
	if ((sin(player->pa + (PI / 2)) * 5) < 0)
		yo = -20;
	else
		yo = 20;
	ipx = player->px / 64.0, ipx_add_xo = (player->px + xo) / 64.0, ipx_sub_xo = (player->px - xo) / 64.0;
	ipy = player->py / 64.0, ipy_add_yo = (player->py + yo) / 64.0, ipy_sub_yo = (player->py - yo) / 64.0;
	if (key.key == MLX_KEY_D)
	{
		if (map[ipy][ipx_add_xo] == '0')
			player->px += cos(player->pa + (PI / 2)) * 5;
		if (map[ipy_add_yo][ipx] == '0')
			player->py += sin(player->pa + (PI / 2)) * 5;
	}
	if (key.key == MLX_KEY_A)
	{
		if (map[ipy][ipx_sub_xo] == '0')
			player->px -= cos(player->pa + (PI / 2)) * 5;
		if (map[ipy_sub_yo][ipx] == '0')
			player->py -= sin(player->pa + (PI / 2)) * 5;
	}
	// player->img->instances[0].x = player->px;
	// player->img->instances[0].y = player->py;
	// player->dir->instances[0].x = player->px + player->pdx * 5;
	// player->dir->instances[0].y = player->py + player->pdy * 5;
	draw_rays_3d(*player, crash);
}

void	paint_text(t_player player)
{
	mlx_texture_t *t = player.textures[3];
	mlx_image_t *img = mlx_new_image(player.mlx, t->width, t->height);
	for (u_int32_t i = 0; i < t->height; i++)
	{
		for (u_int32_t j = 0; j < t->width; j++)
			mlx_put_pixel(img, j, i, t->pixels[(i * t->width + j) * BPP]);
	}
	mlx_image_to_window(player.mlx, img, 0, 0);
}

void	paint_horizon(int32_t color_c, int32_t color_f, void *mlx)
{
	mlx_image_t *ceiling;
	mlx_image_t *floor;

	ceiling = mlx_new_image(mlx, WIN_W, (int32_t)(WIN_H / 2));
	floor = mlx_new_image(mlx, WIN_W, (int32_t)(WIN_H / 2));
	paint_image(ceiling, color_c);
	paint_image(floor, color_f);
	mlx_image_to_window(mlx, ceiling, 0, 0);
	mlx_image_to_window(mlx, floor, 0, WIN_H / 2);
}

int main()
{
	mlx_t		*mlx;
	t_player	player;
	t_map3d		map3d;

	mlx = mlx_init(WIN_W, WIN_H, "Game", false);
	player.px = 300;
	player.py = 300;
	player.pa = PI;
	player.pdx = cos(player.pa) * 5;
	player.pdy = sin(player.pa) * 5;
	player.map3d = &map3d;
	map3d.buffer = ft_calloc(WIN_H, sizeof(uint32_t *));
	for (int i = 0; i < WIN_H; i++)
	{
		map3d.buffer[i] = ft_calloc(WIN_W, sizeof(uint32_t));
	}
	player.mlx = mlx;
	player.img = mlx_new_image(mlx, WIN_W, WIN_H);
	player.textures[0] = mlx_load_png("pics/purplestone.png");
	player.textures[1] = mlx_load_png("pics/greystone.png");
	player.textures[2] = mlx_load_png("pics/mossy.png");
	player.textures[3] = mlx_load_png("pics/colorstone.png");
	crash = mlx_new_image(mlx, 10, 10);
	// draw_map_2d(mlx);
	// draw_player(mlx, &player);
	// for (int i = 0; i < RAYNR; i++)
	// 	mlx_image_to_window(mlx, crash, i, 0);
	// paint_horizon(0x070808FF, 0x222929FF, mlx);
	// paint_text(player);
	// paint_image(player.img, 0xFF0000FF);
	mlx_image_to_window(mlx, player.img, 0, 0);
	draw_rays_3d(player, crash);
	mlx_key_hook(mlx, &buttons, &player);
	mlx_loop(mlx);
	mlx_delete_image(mlx, crash);
	mlx_delete_image(mlx, player.img);
	mlx_terminate(mlx);
	// system("leaks cub3d");
	return (0);
}