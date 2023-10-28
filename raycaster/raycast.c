/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:08:15 by mtravez           #+#    #+#             */
/*   Updated: 2023/10/28 15:55:12 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	set_horizontal_walls(t_player player, t_ray *ray)
{
	if (ray->ra > PI)
	{
		ray->dy[HORIZONTAL] = (((int) player.py >> 6) << 6) - 0.0001;
		ray->yo = -STEPSIZE;
	}
	if (ray->ra <= PI)
	{
		ray->dy[HORIZONTAL] = (((int) player.py >> 6) << 6) + STEPSIZE;
		ray->yo = STEPSIZE;
	}
	ray->dx[HORIZONTAL] = (player.py - ray->dy[HORIZONTAL]) * \
						(-1 / tan(ray->ra)) + player.px;
	ray->xo = -ray->yo * (-1 / tan(ray->ra));
}

void	set_vertical_walls(t_player player, t_ray *ray)
{
	if (ray->ra > PI2 && ray->ra < PI3)
	{
		ray->dx[VERTICAL] = (((int) player.px >> 6) << 6) - 0.0001;
		ray->xo = -STEPSIZE;
	}
	if (ray->ra < PI2 || ray->ra > PI3)
	{
		ray->dx[VERTICAL] = (((int) player.px >> 6) << 6) + STEPSIZE;
		ray->xo = STEPSIZE;
	}
	ray->dy[VERTICAL] = (player.px - ray->dx[VERTICAL]) * \
						-tan(ray->ra) + player.py;
	ray->yo = -ray->xo * -tan(ray->ra);
}

void	draw_rays_3d(t_player player)
{
	t_ray	ray;

	ray.ra = round_up_angle(player.pa - DR * 30);
	ray.r = 0;
	clear_buffer(player.map3d);
	while (ray.r < RAYNR)
	{
		start_ray(&ray, player);
		set_horizontal_walls(player, &ray);
		calculate_ray_dist(&ray, player, HORIZONTAL);
		set_vertical_walls(player, &ray);
		calculate_ray_dist(&ray, player, VERTICAL);
		compare_distance(&ray);
		ray.ra = round_up_angle(ray.ra + (DR / (WIN_W / 60)));
		ray.dist *= cos(round_up_angle(player.pa - ray.ra));
		draw_texture(ray, player);
		ray.r++;
	}
	paint_buffer(player);
}
