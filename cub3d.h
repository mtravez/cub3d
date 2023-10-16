/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmeng <cmeng@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 18:10:49 by mtravez           #+#    #+#             */
/*   Updated: 2023/10/16 15:40:05 by cmeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "lib/MLX42/include/MLX42/MLX42.h"
# include "lib/libft/libft.h"
# include <math.h>
# include <stdio.h>
# define BPP 4UL
# define STEPSIZE 64.0
# define MAPS 64
# define SPEED 8
# define TURN_SPEED 0.1
# define PINK 0xFAA0EFFF
# define SHADOW 0xB876B0FF
# define GROUND 0x0000004B
# define WALL 0xAFFAA04B
# define FLOOR 0x222929FF
# define CEILING 0x070808FF
# define PI M_PI //WEST
# define PI2 M_PI_2 //SOUTH
# define PI3 4.71238898 //NORTH
# define DR 0.0174533
# define WIN_H 750
# define WIN_W 1024
# define RAYNR WIN_W
# define VERTICAL 1
# define HORIZONTAL 0

typedef enum e_direction
{
	EAST,
	SOUTH,
	WEST,
	NORTH
}	t_direction;

typedef struct s_arr
{
	char	**data;
	size_t	size;
	size_t	max_size;
}	t_arr;

typedef struct s_data
{
	t_arr		map;
	size_t		width;
	size_t		height;
	t_direction	player_dir;
	size_t		player_x;
	size_t		player_y;
	char		*ea;
	char		*so;
	char		*we;
	char		*no;
	uint32_t	color_f;
	uint32_t	color_c;
}	t_data;

typedef struct s_map3d
{
	uint32_t	**buffer;
}	t_map3d;

typedef struct s_player
{
	mlx_t			*mlx;
	mlx_image_t		*img;
	mlx_texture_t	*textures[4];
	t_map3d			*map3d;
	t_data			*data;
	float			px;
	float			py;
	float			pdx;
	float			pdy;
	float			pa;
}	t_player;

typedef struct s_ray
{
	int			r;
	int			mx;
	int			my;
	int			mp;
	float		rx;
	float		ry;
	float		ra;
	float		xo;
	float		yo;
	float		dist;
	float		dis_d[2];
	float		dx[2];
	float		dy[2];
	t_direction	wall;
	float		shade;
}	t_ray;

typedef struct s_texture
{
	mlx_texture_t	*t;
	float			tx;
	float			ty;
	float			ty_off;
	float			ty_step;
	int				line_h;
	float			line_o;
}	t_texture;

void		draw_rays_3d(t_player player);
float		get_angle(t_direction dir);
int			get_simbol(float x);
void		free_map(t_map3d *map);
void		delete_textures(t_player *player);
int			arr_create(t_arr *arr);
int			arr_add(t_arr *arr, char *str);
char		*arr_get(t_arr *arr, unsigned long index);
void		arr_free(t_arr *arr);
void		play(t_data data);
void		clear_buffer(t_map3d *map);
void		paint_buffer(t_player player);
uint32_t	get_texcolor(mlx_texture_t *t, uint32_t x, uint32_t y, float shade);
void		set_tex_values(t_ray ray, t_player player, t_texture *t);
float		dist(float ax, float ay, float bx, float by);
void		draw_texture(t_ray ray, t_player player);
void		start_ray(t_ray *ray, t_player player);
void		calculate_ray_dist(t_ray *ray, t_player player, int vh);
void		compare_distance(t_ray *ray);
float		round_up_angle(float angle);

// PARSER
int			handle_input(int argc, char**argv, int *fd);
void		init_data(t_data *data);
int			parser(t_data *data, char **argv, int fd);
int			check_file_type(char *argv);
int			get_identifiers(t_data *data, int fd);
int			get_map(t_data *data, int fd);
int			set_textures(t_data *data, char **frag);
int			set_color(char *str, uint32_t *color);
int			validate_map(t_data *data);
int			check_player(t_data *data);
int			is_player_pos_set(t_data *data);

void		free_2d(char **str, int i);
void		free_textures(t_data *data);
int			str_eq(const char *s1, const char *s2);

#endif