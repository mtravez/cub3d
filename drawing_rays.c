/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_rays.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mtravez <mtravez@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:00:37 by mtravez           #+#    #+#             */
/*   Updated: 2023/10/06 18:24:16 by mtravez          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw_texture(t_ray ray, t_player player)
{
	t_texture	t;
	int			i;
	int32_t		color;

	set_tex_values(ray, player, &t);
	i = 0;
	while (i < t.line_h)
	{
		color = get_texcolor(t.t, (int) t.tx, (int)t.ty, ray.shade);
		player.map3d->buffer[(int)(i + t.line_o)][ray.r] = color;
		t.ty += t.ty_step;
		i++;
	}
	i = 0;
	while (i < WIN_H)
	{
		if (i <= t.line_o)
			color = player.data->color_c;
		if (i >= t.line_h + t.line_o)
			color = player.data->color_f;
		if (i < t.line_o || i > t.line_h + t.line_o)
			player.map3d->buffer[i][ray.r] = color;
		i++;
	}
}

void	start_ray(t_ray *ray, t_player player)
{
	ray->dis_d[HORIZONTAL] = 10000000;
	ray->dx[HORIZONTAL] = player.px;
	ray->dy[HORIZONTAL] = player.py;
	ray->dis_d[VERTICAL] = 10000000;
	ray->dx[VERTICAL] = player.px;
	ray->dy[VERTICAL] = player.py;
}

void	calculate_ray_dist(t_ray *ray, t_player player, int vh)
{
	int	dof;

	dof = 0;
	while (dof < 20)
	{
		ray->mx = (int)(ray->dx[vh]) >> 6;
		ray->my = (int)(ray->dy[vh]) >> 6;
		if (ray->mx >= 0 && ray->my >= 0 && \
			(size_t) ray->mx < player.data->width && \
			(size_t) ray->my < player.data->height && \
			player.data->map.data[ray->my][ray->mx] == '1')
		{
			ray->dis_d[vh] = dist(player.px, player.py, \
				ray->dx[vh], ray->dy[vh]);
			break ;
		}
		ray->dx[vh] += ray->xo;
		ray->dy[vh] += ray->yo;
		dof++;
	}
}

void	compare_distance(t_ray *ray)
{
	if (ray->dis_d[HORIZONTAL] < ray->dis_d[VERTICAL])
	{
		ray->rx = ray->dx[HORIZONTAL];
		ray->ry = ray->dy[HORIZONTAL];
		ray->dist = ray->dis_d[HORIZONTAL];
		ray->shade = 0.8;
		if (ray->yo < 0)
			ray->wall = SOUTH;
		else
			ray->wall = NORTH;
	}
	else
	{
		ray->rx = ray->dx[VERTICAL];
		ray->ry = ray->dy[VERTICAL];
		ray->dist = ray->dis_d[VERTICAL];
		ray->shade = 1;
		if (ray->xo < 0)
			ray->wall = WEST;
		else
			ray->wall = EAST;
	}
}

float	round_up_angle(float angle)
{
	if (angle < 0)
		angle += 2 * PI;
	if (angle > 2 * PI)
		angle -= 2 * PI;
	return (angle);
}
