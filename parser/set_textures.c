/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:37:44 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/23 13:27:34 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"
#include <fcntl.h>

int	set_textures(t_data *data, char **frag)
{
	int		fd;
	char	*path;

	fd = 0;
	path = ft_substr(frag[1], 0, ft_strlen(frag[1]) - 1);
	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (free(path), 1);
	if (str_eq(frag[0], "EA\0") && data->ea == NULL)
		data->ea = ft_substr(frag[1], 0, ft_strlen(frag[1]) - 1);
	else if (str_eq(frag[0], "SO\0") && data->so == NULL)
		data->so = ft_substr(frag[1], 0, ft_strlen(frag[1]) - 1);
	else if (str_eq(frag[0], "WE\0") && data->we == NULL)
		data->we = ft_substr(frag[1], 0, ft_strlen(frag[1]) - 1);
	else if (str_eq(frag[0], "NO\0") && data->no == NULL)
		data->no = ft_substr(frag[1], 0, ft_strlen(frag[1]) - 1);
	return (free(path), 0);
}
