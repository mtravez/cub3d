/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:39:44 by cmeng             #+#    #+#             */
/*   Updated: 2023/10/16 17:37:10 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

static int	rgb_to_uint(char **frag, uint32_t *color)
{
	int	red;
	int	green;
	int	blue;

	if (frag[0][0] == '\n' || frag[1][0] == '\n' || frag[2][0] == '\n')
		return (1);
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
	char	**frag;
	int		i;

	frag = ft_split(str, ',');
	i = 0;
	while (frag[i] != NULL)
		i++;
	if (i != 3)
		return (free_2d(frag, i), free(str), 1);
	if (rgb_to_uint(frag, color))
		return (free_2d(frag, i), free(str), 1);
	free_2d(frag, i);
	free(str);
	return (0);
}
