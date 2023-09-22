/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_identifier.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:46:53 by christianme       #+#    #+#             */
/*   Updated: 2023/09/22 15:09:14 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	rgb_to_uint(char **frag, uint32_t *color)
{
	int	red;
	int	green;
	int	blue;

	red = atoi(frag[0]);
	green = atoi(frag[1]);
	blue = atoi(frag[2]);
	if (red < 0 || green < 0 || blue < 0)
		return (1);
	if (red > 255 || green > 255 || blue > 255)
		return (1);
	*color = ((red << 24) | (green << 16) | (blue << 8) | 255);
	return (0);
}

static int	set_color(char *str, uint32_t *color)
{
	char	**frag;
	int		i;

	frag = ft_split(str, ',');
	i = 0;
	while (frag[i])
		i++;
	if (i != 3)
		return (free_2d(frag, i), free(str), 1);
	if (rgb_to_uint(frag, color))
		return (free_2d(frag, i), free(str), 1);
	free_2d(frag, i);
	free(str);
	return (0);
}

static int	set_id(t_data *data, char **frag)
{
	if (str_eq(frag[0], "EA\0") && data->ea == NULL)
		data->ea = ft_substr(frag[1], 0, ft_strlen(frag[1]) - 1);
	else if (str_eq(frag[0], "SO\0") && data->so == NULL)
		data->so = ft_substr(frag[1], 0, ft_strlen(frag[1]) - 1);
	else if (str_eq(frag[0], "WE\0") && data->we == NULL)
		data->we = ft_substr(frag[1], 0, ft_strlen(frag[1]) - 1);
	else if (str_eq(frag[0], "NO\0") && data->no == NULL)
		data->no = ft_substr(frag[1], 0, ft_strlen(frag[1]) - 1);
	else if (str_eq(frag[0], "F\0"))
	{
		if (set_color(ft_strdup(frag[1]), &data->color_f))
			return (1);
	}
	else if (str_eq(frag[0], "C\0"))
	{
		if (set_color(ft_strdup(frag[1]), &data->color_c))
			return (1);
	}
	else
		return (free(frag), 1);
	return (0);
}

static int	all_ids_set(t_data *data)
{
	if ((data->ea != NULL)
		&& (data->so != NULL)
		&& (data->we != NULL)
		&& (data->no != NULL)
		&& (data->color_c != 0)
		&& (data->color_f != 0))
		return (1);
	else
		return (0);
}

int	get_identifiers(t_data *data, int fd)
{
	char	*line;
	char	**frag;
	int		i;

	line = get_next_line(fd);
	while (line != NULL && !all_ids_set(data))
	{
		i = 0;
		if (line[0] != '\n')
		{
			frag = ft_split(line, ' ');
			while (frag[i])
				i++;
			if (i != 2)
				return (free_2d(frag, i), free(line), 1);
			if (set_id(data, frag))
				return (free_2d(frag, i), free(line), 1);
			free_2d(frag, i);
		}
		free(line);
		line = get_next_line(fd);
		if (line == NULL && !all_ids_set(data))
			return (free(line), 1);
	}
	return (free(line), 0);
}
