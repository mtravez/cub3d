/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:58:27 by christianme       #+#    #+#             */
/*   Updated: 2023/10/23 16:41:34 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	handle_end_map(t_data *data, char *line, int i)
{
	size_t	len;

	if (arr_add(&data->map, line))
		return (1);
	len = ft_strlen(data->map.data[i]) - 1;
	if (len > data->width)
		data->width = len;
	if (data->map.data[i][len] == '\n')
		data->map.data[i][len] = '\0';
	return (0);
}

static int	get_lines(t_data *data, char *line, int fd)
{
	int		i;
	int		end_map;

	i = 0;
	end_map = 0;
	while (line != NULL)
	{
		if (line[0] == '\n')
		{
			end_map = 1;
			free(line);
		}
		if (!end_map && handle_end_map(data, line, i))
			return (1);
		line = get_next_line(fd);
		if (line == NULL)
			return (free(line), 0);
		if (line[0] != '\n' && end_map)
			return (free(line), 1);
		i++;
	}
	return (0);
}

int	get_map(t_data *data, int fd)
{
	char	*line;

	line = get_next_line(fd);
	if (line == NULL)
		return (1);
	while (line[0] == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	if (arr_create(&data->map))
		return (arr_free(&data->map), 1);
	if (get_lines(data, line, fd))
		return (arr_free(&data->map), 1);
	return (0);
}
