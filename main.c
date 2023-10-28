/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 15:56:32 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/28 15:56:45 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		fd;

	if (handle_input(argc, argv, &fd))
		return (1);
	init_data(&data);
	if (parser(&data, argv, fd))
		return (close(fd), free_gnl(), 1);
	if (play(data))
		return (free_textures(&data), free_2d(data.map.data, data.map.size), 1);
	free_textures(&data);
	free_2d(data.map.data, data.map.size);
}
