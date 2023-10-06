/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 18:04:11 by mtravez           #+#    #+#             */
/*   Updated: 2023/10/01 18:11:37 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		mlx_delete_texture(player->textures[i]);
		i++;
	}
}