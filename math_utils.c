/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 18:04:11 by mtravez           #+#    #+#             */
/*   Updated: 2023/10/23 13:29:42 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_textures(t_player *player, t_data *data)
{
	int	i;

	player->textures[EAST] = mlx_load_png((const char *)data->ea);
	player->textures[SOUTH] = mlx_load_png((const char *)data->so);
	player->textures[WEST] = mlx_load_png((const char *)data->we);
	player->textures[NORTH] = mlx_load_png((const char *)data->no);
	i = 0;
	while (i < 4)
	{
		if (!player->textures[i] || \
			player->textures[i]->height != player->textures[i]->width)
		{
			if (player->textures[i])
				write(STDERR_FILENO, "Textures can only be square\n", 28);
			else
				write(STDERR_FILENO, "Failed to create texture\n", 25);
			delete_textures(player);
			return (0);
		}
		i++;
	}
	return (1);
}

float	get_angle(t_direction dir)
{
	if (dir == EAST)
		return (PI);
	if (dir == SOUTH)
		return (PI2);
	if (dir == WEST)
		return (0);
	return (PI3);
}

int	get_simbol(float x)
{
	if (x < 0)
		return (-1);
	return (1);
}

void	free_map(t_map3d *map)
{
	int	i;

	i = 0;
	while (i < WIN_H)
	{
		free(map->buffer[i]);
		i++;
	}
	free(map->buffer);
}

void	delete_textures(t_player *player)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (player->textures[i])
		{
			mlx_delete_texture(player->textures[i]);
			player->textures[i] = NULL;
		}
		i++;
	}
}
