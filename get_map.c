#include "cub3d.h"

int	get_map(t_data *data, int fd)
{
	char *line;
	int i;
	size_t	len;
	
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
		line = get_next_line(fd);
		if (line == NULL)
			return (free(line), 0);	
		i++;
	}
	return (0);
}