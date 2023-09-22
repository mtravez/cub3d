/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 11:58:27 by christianme       #+#    #+#             */
/*   Updated: 2023/09/22 14:33:51 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	get_lines(t_data *data, char *line, int fd)
{
	int		i;
	size_t	len;

	i = 0;
	while (line != NULL)
	{
		if (line[0] == '\n')
			return (free(line), arr_free(&data->map), 1);
		if (arr_add(&data->map, line))
			return (1);
		len = ft_strlen(data->map.data[i]) - 1;
		if (len > data->width)
			data->width = len;
		if (data->map.data[i][len] == '\n')
			data->map.data[i][len] = '\0';
		line = get_next_line(fd);
		if (line == NULL)
			return (free(line), 0);
		i++;
	}
	return (0);
}

int	get_map(t_data *data, int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line[0] == '\n')
	{
		free(line);
		line = get_next_line(fd);
	}
	if (arr_create(&data->map))
		return (1);
	if (get_lines(data, line, fd))
		return (1);
	return (0);
}
