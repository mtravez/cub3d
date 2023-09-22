/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/22 12:00:22 by christianme       #+#    #+#             */
/*   Updated: 2023/09/22 14:35:35 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "../cub3d.h"

void	init_data(t_data *data)
{
	data->width = 0;
	data->ea = NULL;
	data->so = NULL;
	data->we = NULL;
	data->no = NULL;
	data->color_f = 0;
	data->color_c = 0;
	data->player_dir = 4;
}

int	handle_input(int argc, char**argv, int *fd)
{
	if (argc < 2)
		return (printf("Error\nWrong amount args\n"), 1);
	*fd = open(argv[1], O_RDONLY);
	if (*fd == -1)
		return (close(*fd), printf("Error\nopen() failed\n"), 1);
	if (read(*fd, NULL, 0) < 0)
		return (close(*fd), printf("Error\nread() failed\n"), 1);
	else
		return (0);
}
