/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/21 17:21:07 by mtravez           #+#    #+#             */
/*   Updated: 2023/10/28 15:54:49 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	handle_angle_change(mlx_key_data_t key, t_player *player)
{
	if (key.key == MLX_KEY_LEFT)
	{
		player->pa -= TURN_SPEED;
		if (player->pa < 0)
			player->pa += 2 * PI;
	}
	if (key.key == MLX_KEY_RIGHT)
	{
		player->pa += TURN_SPEED;
		if (player->pa > 2 * PI)
			player->pa -= 2 * PI;
	}
	player->pdx = cos(player->pa) * 5;
	player->pdy = sin(player->pa) * 5;
}

void	handle_movement(mlx_key_data_t key, t_player *player, float x, float y)
{
	int	xo;
	int	yo;

	xo = 20 * get_simbol(x);
	yo = 20 * get_simbol(y);
	if (key.key == MLX_KEY_W || key.key == MLX_KEY_D)
	{
		if (player->data->map.data[(int)(player->py / STEPSIZE)] \
			[(int)((player->px + xo) / STEPSIZE)] != '1')
			player->px += x;
		if (player->data->map.data[(int)((player->py + yo) / STEPSIZE)] \
			[(int)(player->px / STEPSIZE)] != '1')
			player->py += y;
	}
	if (key.key == MLX_KEY_S || key.key == MLX_KEY_A)
	{
		if (player->data->map.data[(int)(player->py / STEPSIZE)] \
			[(int)((player->px - xo) / STEPSIZE)] != '1')
			player->px -= x;
		if (player->data->map.data[(int)((player->py - yo) / STEPSIZE)] \
			[(int)(player->px / STEPSIZE)] != '1')
			player->py -= y;
	}
}

void	buttons(mlx_key_data_t key, void *param)
{
	t_player	*player;

	player = param;
	if (key.key == MLX_KEY_LEFT || key.key == MLX_KEY_RIGHT)
		handle_angle_change(key, player);
	if (key.key == MLX_KEY_W || key.key == MLX_KEY_S)
		handle_movement(key, player, player->pdx, player->pdy);
	if (key.key == MLX_KEY_A || key.key == MLX_KEY_D)
		handle_movement(key, player, cos(player->pa + (PI / 2)) * 5, \
		sin(player->pa + (PI / 2)) * 5);
	if (key.key == MLX_KEY_ESCAPE)
		mlx_close_window(player->mlx);
	draw_rays_3d(*player);
}

void	set_player(t_data *data, t_player *player)
{
	int	i;

	player->data = data;
	player->px = (data->player_x * STEPSIZE) + STEPSIZE / 2;
	player->py = (data->player_y * STEPSIZE) + STEPSIZE / 2;
	player->pa = get_angle(data->player_dir);
	player->pdx = cos(player->pa) * 5;
	player->pdy = sin(player->pa) * 5;
	if (!check_textures(player, data))
		return ;
	player->img = mlx_new_image(player->mlx, WIN_W, WIN_H);
	player->map3d->buffer = ft_calloc(WIN_H, sizeof(uint32_t *));
	i = -1;
	while (++i < WIN_H)
		player->map3d->buffer[i] = ft_calloc(WIN_W, sizeof(uint32_t));
}

int	play(t_data data)
{
	mlx_t		*mlx;
	t_player	player;
	t_map3d		map3d;

	mlx = mlx_init(WIN_W, WIN_H, "Game", false);
	player.mlx = mlx;
	player.map3d = &map3d;
	set_player(&data, &player);
	if (!player.textures[0])
	{
		mlx_terminate(mlx);
		return (1);
	}
	mlx_image_to_window(mlx, player.img, 0, 0);
	draw_rays_3d(player);
	mlx_key_hook(mlx, &buttons, &player);
	mlx_loop(mlx);
	mlx_delete_image(mlx, player.img);
	delete_textures(&player);
	free_map(&map3d);
	mlx_terminate(mlx);
	return (0);
}
