#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_data	data;
	int		fd;

	if (handle_input(argc, argv, &fd))
		return (1);
	init_data(&data);
	if (parser(&data, argv, fd))
		return (close(fd), 1);
	size_t i = 0;
	while (i < data.map.size)
	{
		printf("m: %s\n", data.map.data[i]);
		i++;
	}
	// if (RAYCASTER())
	// 	return (1);
	play(data);
	free_textures(&data);
	free_2d(data.map.data, data.map.size);
	return (printf("Success\n"), 0);
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