#include "cub3d.h"

static int	flood(size_t y, size_t x, size_t h, size_t w, char **map)
{
	if (y < 0 || x < 0 || map[y] == NULL || map[y][x] == '\0')
        return 0;
	if (map[y][x] == ' ')
		return (1);
	if (map[y][x] == '0' && (x == 0 || y == 0 || x == (w - 1) || y == (h - 1)))
		return (1);	
	if (map[y][x] == '1')
        return (0);		
	map[y][x] = '1';
	if (flood(y - 1, x, h, w, map) 
		|| flood(y + 1, x, h, w, map) 
		|| flood(y, x - 1, h, w,map) 
		|| flood(y, x + 1, h, w, map))
        return (1);
	return (0);
}

static int	floodfill(t_data *data)
{
	char	**map_dup;
	size_t	i;

	
	map_dup = malloc(data->height * sizeof(char *));
    if (map_dup == NULL)
		return (1);
	i = 0;
	while (i < data->height)
	{
		map_dup[i] = ft_strdup(data->map.data[i]);
		// printf("%s\n", map_dup[i]);
		i++;
	}
	if (flood(data->player_y, data->player_x, data->height, data->width, map_dup))
		return (free_2d(map_dup, data->height - 1), 1);
	i = 0;
	free_2d(map_dup, data->height - 1);
	return (0);
	
}	

static int	is_player_pos_set(t_data *data)
{
	if (data->player_dir >= 0 && data->player_dir < 4)
		return (1);
	return (0);	
}

static int	player_position(t_data *data, size_t y, size_t x)
{
	char c;

	c = data->map.data[y][x];
	if ((c == 'E' || c == 'S' || c == 'W' || c == 'N') && is_player_pos_set(data))
		return (1);
	else if ((c == 'E' || c == 'S' || c == 'W' || c == 'N') && !is_player_pos_set(data))
	{
		data->player_x = x;
		data->player_y = y;
		if (c == 'E')
			data->player_dir = EAST;
		else if (c == 'S')
			data->player_dir = SOUTH;
		else if (c == 'W')
			data->player_dir = WEST;
		else if (c == 'N')
			data->player_dir = NORTH;					
	}
	return (0);
}


static int	invalid_character(char c)
{
	if (c != ' ' && c != '0' && c != '1' && c != 'E' && c != 'S' && c != 'W' && c != 'N')
		return (1);
	return (0);	
}

static int	check_player(t_data *data)
{
	size_t y;
	size_t x;

	y = 0;
	while (y < data->map.size)
	{
		x = 0;	
        while (x < data->width)
		{
        	if (invalid_character(data->map.data[y][x]))
				return (1);
			if (player_position(data, y, x))
				return (1);	
			x++;	
        }
        y++;
	}
	data->height = data->map.size;
	return (0);
}

static int	standartise_map(t_data *data)
{
	size_t i;
	size_t j;
	char *str;

	i = 0;
	while (i < data->map.size)
	{
        str = malloc((data->width + 1) * sizeof(char));
        if (str == NULL)
            return (1);
		j = 0;	
        while (j < data->width)
        {	
            if (j < ft_strlen(data->map.data[i]))
                str[j] = data->map.data[i][j];
            else
                str[j] = ' ';
            j++;
        }
        str[data->width] = '\0';
		free(data->map.data[i]);
		data->map.data[i] = str;
        i++;
	}
	return (0);
}

int	validate_map(t_data *data)
{
	if (standartise_map(data))
		return (1);
	if (check_player(data))
		return (1);
	if (!is_player_pos_set(data))
		return (1);
	if (floodfill(data))
		return (1);		
	return (0);
}