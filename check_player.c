/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_player.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christianmeng <christianmeng@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:41:06 by christianme       #+#    #+#             */
/*   Updated: 2023/09/22 11:46:33 by christianme      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	player_position(t_data *data, size_t y, size_t x)
{
	char	c;

	c = data->map.data[y][x];
	if ((c == 'E' || c == 'S' || c == 'W' || c == 'N')
		&& is_player_pos_set(data))
		return (1);
	else if ((c == 'E' || c == 'S' || c == 'W' || c == 'N')
		&& !is_player_pos_set(data))
	{
		data->player_x = x;
		data->player_y = y;
		if (c == 'E')
			data->player_dir = EAST;
		else if (c == 'S')
			data->player_dir = SOUTH;
		else if (c == 'W')
			data->player_dir = WEST;
		else if (c == 'N')
			data->player_dir = NORTH;
	}
	return (0);
}

static int	invalid_character(char c)
{
	if (c != ' ' && c != '0' && c != '1' && c != 'E'
		&& c != 'S' && c != 'W' && c != 'N')
		return (1);
	return (0);
}

int	is_player_pos_set(t_data *data)
{
	if (data->player_dir >= 0 && data->player_dir < 4)
		return (1);
	return (0);
}

int	check_player(t_data *data)
{
	size_t	y;
	size_t	x;

	y = 0;
	while (y < data->map.size)
	{
		x = 0;
		while (x < data->width)
		{
			if (invalid_character(data->map.data[y][x]))
				return (1);
			if (player_position(data, y, x))
				return (1);
			x++;
		}
		y++;
	}
	data->height = data->map.size;
	return (0);
}
