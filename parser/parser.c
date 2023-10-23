/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:01:37 by christianme       #+#    #+#             */
/*   Updated: 2023/10/23 13:23:23 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_file_type(char *argv)
{
	int		i;
	char	*typ;

	i = 0;
	typ = ".cub";
	while (argv[i] != '.')
		i++;
	while (argv[i] != '\0')
		if (argv[i++] != *typ++)
			return (1);
	return (0);
}

int	parser(t_data *data, char **argv, int fd)
{
	if (check_file_type(argv[1]))
		return (printf("Error\nYou need a .cub file\n"), 1);
	if (get_identifiers(data, fd))
		return (free_textures(data),
			printf("Error\nFetching Identificators failed\n"), 1);
	if (get_map(data, fd))
		return (free_textures(data), printf("Error\nFetching map failed\n"), 1);
	if (validate_map(data))
		return (free_textures(data),
			arr_free(&data->map), printf("Error\nInvalid map\n"), 1);
	return (0);
}
