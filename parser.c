#include "cub3d.h"
#include <fcntl.h>
#include <unistd.h>

// int	validate_map(t_data data)
// {
	// TODO: Fill up the lines with spaces until width 
	//		 Go through the map and check Player 
	// 		 Floodfill to check if map is valid

// 	return (0);
// }

int get_map(t_data *data, int fd)
{
	char *line;
	int i;
	int	len;
	
	line = get_next_line(fd);
	i = 0;
	while (line[0] == '\n')
		line = get_next_line(fd);	
	if (arr_create(&data->map))
		return (1);
	while (line != NULL) 
	{
		if (line[0] == '\n')
			return(free(line), arr_free(&data->map), 1);	
		if (arr_add(&data->map, line))
			return (1);
		len = ft_strlen(data->map.data[i]) - 1;
		if (len > data->width)
			data->width = len;
		if (data->map.data[i][len] == '\n')		
			data->map.data[i][len] = '\0';	
		// printf("len: %lu", ft_strlen(data->map.data[i]));	
		printf("s: %s\n", data->map.data[i]);	
		line = get_next_line(fd);
		if (line == NULL)
			return (free(line), arr_free(&data->map), 0);	
		data->height = i++;		
		// printf("width: %i\n", data->width);	
	}
	return (0);
}

// utils
// -------------------------------------------------------//

void	free_2d(char **str, int i)
{
	while (i != 0)
	{
		free(str[i - 1]);
		i--;
	}
	free(str);
}

int	str_cmp(const char *s1, const char *s2)
{
	const unsigned char	*a;
	const unsigned char	*b;

	a = (const unsigned char *) s1;
	b = (const unsigned char *) s2;
	while (1)
	{
		if (*a == '\0' || *b == '\0' || *a != *b)
			return (*a - *b);
		a++;
		b++;
	}
	return (*a - *b);
}

int	str_eq(const char *s1, const char *s2)
{
	return (str_cmp(s1, s2) == 0);
}

// get_identifier()
// -------------------------------------------------------//

int	RGB_to_uint(char **frag, uint32_t *color)
{
	int	red;
	int	green;
	int	blue;

	red = atoi(frag[0]);
	green = atoi(frag[1]);
	blue = atoi(frag[2]);

	if (red < 0 || green < 0 || blue < 0)
		return (1);
	if (red > 255 || green > 255 || blue > 255)	
		return (1);
	*color = ((red << 24) | (green << 16) | (blue << 8) | 255);
	return (0);
}

int	set_color(char *str, uint32_t *color)
{
	char **frag;
	int i;

	frag = ft_split(str, ',');
	i = 0;
	while(frag[i])
			i++;
	if (i != 3)
		return (free_2d(frag, i), 1);
	if (RGB_to_uint(frag, color))
		return (free_2d(frag, i), 1);
	// printf("color: %u\n", *color);
	return (0);
}

int	set_id(t_data *data, char **frag)
{
	if (str_eq(frag[0], "EA\0") && data->ea == NULL)
		data->ea = ft_strdup(frag[1]);
	else if (str_eq(frag[0], "SO\0") && data->so == NULL)
		data->so = ft_strdup(frag[1]);
	else if (str_eq(frag[0], "WE\0") && data->we == NULL)
		data->we = ft_strdup(frag[1]);
	else if (str_eq(frag[0], "NO\0") && data->no == NULL)
		data->no = ft_strdup(frag[1]);

	else if (str_eq(frag[0], "F\0"))
	{
		if (set_color(ft_strdup(frag[1]), &data->color_f))
			return (1);
	}
	else if (str_eq(frag[0], "C\0"))
	{
		if (set_color(ft_strdup(frag[1]), &data->color_c))
			return (1);
	}
	else 
		return (1);
	return (0);	
}

int	all_ids_set(t_data *data)
{
	if ((data->ea != NULL) &&
		(data->so != NULL) &&
		(data->we != NULL) &&
		(data->no != NULL) &&
		(data->color_c != 0) &&
		(data->color_f != 0))
			return (1);
	else 
		return (0);		
}

int	get_identifiers(t_data *data, int fd)
{
	char *line;
	char **frag;
	int i;

	i = 0;
	line = get_next_line(fd);
	while (line != NULL && !all_ids_set(data)) 
	{
		if (line[0] != '\n')
		{
			frag = ft_split(line, ' ');
			while(frag[i])
				i++;
			if (i != 2)
				return (free(frag), 1);
			if (set_id(data, frag))
				return (free_2d(frag, i), 1);
			free_2d(frag, i);
			free(line);	
		}	
		line = get_next_line(fd);
		if (line == NULL && !all_ids_set(data))
			return (free(line), 1);	
	}
	return (0);
}

// check_file_type()
// -------------------------------------------------------//
int check_file_type(char *argv)
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

int parser(t_data *data, char **argv, int fd)
{
	(void) data;
	if (check_file_type(argv[1]))
		return (close(fd), printf("Error\nYou need a .cub file\n"), 1);
	if (get_identifiers(data, fd))
		return (close(fd), printf("Error\nFetching Identificators failed\n"), 1);
	if (get_map(data, fd))
		return (close(fd), printf("Error\nFetching map failed\n"), 1);	
	// if (validate_map(data))
	// 	return (1);	
	return (0);	
}

void	init_data(t_data *data)
{
	// data->map = NULL;
	data->height = 0;
	data->width = 0;
	// data->player_dir =
	// data->player_x =
	// data->player_y =
	data->ea = NULL;
	data->so = NULL;
	data->we = NULL;
	data->no = NULL;
	data->color_f = 0;
	data->color_c = 0;

}

int	handle_input(int argc, char**argv, int *fd)
{
	if (argc < 2)
		return (printf("Error\nWrong amount args\n"), 1);
	*fd = open(argv[1], O_RDONLY);
	if (*fd == -1)
		return(close(*fd), printf("Error\nopen() failed\n"), 1);
	if (read(*fd, NULL, 0) < 0)
		return (close(*fd), printf("Error\nread() failed\n"), 1);
	else
		return (0);	 
}

int	main (int argc, char **argv)
{
	t_data	data;
	int		fd;

	if (handle_input(argc, argv, &fd))
		return (1);
	init_data(&data);	
	if (parser(&data, argv, fd))
		return (close(fd), 1);	
	// if (RAYCASTER())
	// 	return (1);
	return (printf("Success\n"), 0);	
}