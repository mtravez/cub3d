#include "cub3d.h"


int	check_file_type(char *argv)
{
	int i;
	char *typ;

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
		return (close(fd), printf("Error\nYou need a .cub file\n"), 1);
	if (get_identifiers(data, fd))
		return (close(fd), printf("Error\nFetching Identificators failed\n"), 1);
	if (get_map(data, fd))
		return (close(fd), printf("Error\nFetching map failed\n"), 1);	
	if (validate_map(data))
		return (close(fd), arr_free(&data->map), printf("Error\nInvalid map\n"), 1);	
	
	return (0);	
}