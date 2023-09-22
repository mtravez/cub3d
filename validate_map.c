/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: christianmeng <christianmeng@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:12:20 by christianme       #+#    #+#             */
/*   Updated: 2023/09/22 12:37:11 by christianme      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	flood(size_t y, size_t x, t_data *data, char **map)
{
	size_t	h;
	size_t	w;

	h = data->height;
	w = data->width;
	if (map[y] == NULL || map[y][x] == '\0')
		return (0);
	if (map[y][x] == ' ')
		return (1);
	if (map[y][x] == '0' && (x == 0 || y == 0 || x == (w - 1) || y == (h - 1)))
		return (1);
	if (map[y][x] == '1')
		return (0);
	map[y][x] = '1';
	if (flood(y - 1, x, data, map) || flood(y - 1, x - 1, data, map)
		|| flood(y - 1, x + 1, data, map) || flood(y, x - 1, data, map)
		|| flood(y, x + 1, data, map) || flood(y + 1, x, data, map)
		|| flood(y + 1, x - 1, data, map) || flood(y + 1, x + 1, data, map))
		return (1);
	return (0);
}

static int	floodfill(t_data *data)
{
	char	**map_dup;
	size_t	i;

	map_dup = malloc(data->height * sizeof(char *));
	if (map_dup == NULL)
		return (1);
	i = 0;
	while (i < data->height)
	{
		map_dup[i] = ft_strdup(data->map.data[i]);
		i++;
	}
	if (flood(data->player_y, data->player_x, data, map_dup))
		return (free_2d(map_dup, data->height), 1);
	i = 0;
	free_2d(map_dup, data->height);
	return (0);
}

static int	standartise_map(t_data *data)
{
	size_t	i;
	size_t	j;
	char	*str;

	i = 0;
	while (i < data->map.size)
	{
		str = malloc((data->width + 1) * sizeof(char));
		if (str == NULL)
			return (1);
		j = 0;
		while (j < data->width)
		{
			if (j < ft_strlen(data->map.data[i]))
				str[j] = data->map.data[i][j];
			else
				str[j] = ' ';
			j++;
		}
		str[data->width] = '\0';
		free(data->map.data[i]);
		data->map.data[i] = str;
		i++;
	}
	return (0);
}

int	validate_map(t_data *data)
{
	if (standartise_map(data))
		return (1);
	if (check_player(data))
		return (1);
	if (!is_player_pos_set(data))
		return (1);
	if (floodfill(data))
		return (1);
	return (0);
}
