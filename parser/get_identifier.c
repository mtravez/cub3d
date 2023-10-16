/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_identifier.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:46:53 by christianme       #+#    #+#             */
/*   Updated: 2023/10/16 17:27:37 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	set_id(t_data *data, char **frag)
{
	int	i;

	i = 0;
	while (frag[i] != NULL)
		i++;
	if (str_eq(frag[0], "F\0"))
	{
		if (set_color(ft_strdup(frag[1]), &data->color_f))
			return (1);
	}
	else if (str_eq(frag[0], "C\0"))
	{
		if (set_color(ft_strdup(frag[1]), &data->color_c))
			return (1);
	}
	else if ((str_eq(frag[0], "EA\0")) || (str_eq(frag[0], "SO\0"))
		|| (str_eq(frag[0], "WE\0")) || (str_eq(frag[0], "NO\0")))
	{
		if (set_textures(data, frag))
			return (1);
	}
	else
		return (1);
		// return (free_2d(frag, i), 1);
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
