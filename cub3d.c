/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:21:07 by mtravez           #+#    #+#             */
/*   Updated: 2023/08/27 18:00:09 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char map[8][8] = {
	{'1','1','1','1','1','1','1','1'},
	{'1','0','0','0','0','0','0','1'},
	{'1','0','1','0','0','0','0','1'},
	{'1','1','1','0','0','0','0','1'},
	{'1','0','0','0','0','0','0','1'},
	{'1','0','0','0','0','1','0','1'},
	{'1','0','1','0','0','1','0','1'},
	{'1','1','1','1','1','1','1','1'}
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
			mlx_put_pixel(img, i, j, color);
			j++;
		}
		i++;
	}
}

void	delete_map(mlx_t *mlx, t_map3d *map3d)
{
	int	i;

	i = 0;
	while (i < RAYNR)
	{
		mlx_delete_image(mlx, map3d->map_3d[i]);
		i++;
	}
}

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
		player->pdx = cos(player->pa) * 5;
		player->pdy = sin(player->pa) * 5;
	}
	if (key.key == MLX_KEY_RIGHT)
	{
		player->pa += 0.1;
		if (player->pa > 2 * PI)
			player->pa -= 2 * PI;
		player->pdx = cos(player->pa) * 5;
		player->pdy = sin(player->pa) * 5;
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
	draw_rays_3d(*player, crash, player->map3d);
}

// void	display(void *player)
// {
// 	t_player *player = player;

	
// }

int main()
{
	void		*mlx;
	t_player	player;
	t_map3d		map3d;

	mlx = mlx_init(WIN_W, WIN_H, "Game", true);
	player.px = 300;
	player.py = 300;
	player.pa = PI3;
	player.pdx = cos(player.pa) * 5;
	player.pdy = sin(player.pa) * 5;
	player.map3d = &map3d;
	player.mlx = mlx;
	crash = mlx_new_image(mlx, 10, 10);
	// paint_image(crash, 0xFF0000FF);
	draw_map_2d(mlx);
	// draw_player(mlx, &player);
	// for (int i = 0; i < RAYNR; i++)
	// 	mlx_image_to_window(mlx, crash, i, 0);
	draw_rays_3d(player, crash, player.map3d);
	mlx_key_hook(mlx, &buttons, &player);
	mlx_loop(mlx);
	mlx_delete_image(mlx, crash);
	for (int i = 0; i < RAYNR; i++)
	{
		mlx_delete_image(mlx, map3d.map_3d[i]);
	}
	mlx_terminate(mlx);
	// system("leaks cub3d");
	return (0);
}