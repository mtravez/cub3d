/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 17:50:47 by mtravez           #+#    #+#             */
/*   Updated: 2023/10/28 15:55:09 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

float	dist(float ax, float ay, float bx, float by)
{
	return (sqrt((bx - ax) * (bx - ax) + (by - ay) * (by - ay)));
}

void	clear_buffer(t_map3d *map)
{
	u_int32_t	i;
	u_int32_t	j;

	i = 0;
	while (i < WIN_H)
	{
		j = 0;
		while (j < WIN_W)
		{
			map->buffer[i][j] = 0;
			j++;
		}
		i++;
	}
}

void	paint_buffer(t_player player)
{
	u_int32_t	i;
	u_int32_t	j;

	i = 0;
	while (i < WIN_H)
	{
		j = 0;
		while (j < WIN_W)
		{
			mlx_put_pixel(player.img, j, i, player.map3d->buffer[i][j]);
			j++;
		}
		i++;
	}
}

uint32_t	get_texcolor(mlx_texture_t *t, uint32_t x, uint32_t y, float shade)
{
	uint32_t	color;

	color = (int)(t->pixels[t->height * y * BPP + x * BPP] * shade) << 24 | \
	(int)(t->pixels[t->height * y * BPP + x * BPP + 1] * shade) << 16 | \
	(int)(t->pixels[t->height * y * BPP + x * BPP + 2] * shade) << 8 | \
	t->pixels[t->height * y * BPP + x * BPP + 3];
	return (color);
}

void	set_tex_values(t_ray ray, t_player player, t_texture *t)
{
	t->line_h = (WIN_H * STEPSIZE) / ray.dist;
	t->t = player.textures[ray.wall];
	t->ty_step = 1.0 * t->t->height / t->line_h;
	t->ty_off = 0;
	if (t->line_h > WIN_H)
	{
		t->ty_off = (t->line_h - WIN_H) / 2.0;
		t->line_h = WIN_H;
	}
	t->line_o = (WIN_H / 2) - (t->line_h / 2);
	t->ty = t->ty_off * t->ty_step;
	if (ray.dis_d[VERTICAL] > ray.dis_d[HORIZONTAL])
	{
		t->tx = (int)(ray.rx * (t->t->width / STEPSIZE)) % t->t->width;
		if (ray.ra > PI)
			t->tx = t->t->width - t->tx - 1;
	}
	else
	{
		t->tx = (int)(ray.ry * (t->t->width / STEPSIZE)) % t->t->width;
		if (ray.ra > PI2 && ray.ra < PI3)
			t->tx = t->t->width - t->tx - 1;
	}
}
