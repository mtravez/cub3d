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
	// if (RAYCASTER())
	// 	return (1);
	if (play(data))
		return (free_textures(&data), free_2d(data.map.data, data.map.size), 1);
	free_textures(&data);
	free_2d(data.map.data, data.map.size);
}

// TESTS

// size_t i = 0;
// while (i < data.map.size)
// {
// 	printf("m: %s\n", data.map.data[i]);
// 	i++;
// }
// printf("y-axis:	%zu\n", data.map.size);
// printf("height:	%zu\n", data.height);
// printf("x-axis:	%zu\n", data.width);
// printf("p-dir:	%u\n", data.player_dir);
// printf("p-y:	%zu\n", data.player_y);
// printf("p-x:	%zu\n", data.player_x);