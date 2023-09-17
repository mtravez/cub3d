# include "lib/MLX42/include/MLX42/MLX42.h"
# include "lib/libft/libft.h"
# include <math.h>
# include <stdio.h>
# define BPP sizeof(int32_t)
# define MAPY 10
# define MAPX 10
# define MAPSIZE 10
# define MAPS 100
# define PINK 0xFAA0EFFF
# define SHADOW 0xB876B0FF
# define GROUND 0x0000004B
# define WALL 0xAFFAA04B
# define FLOOR 0x222929FF
# define CEILING 0x070808FF
# define PI 3.14159265359 //WEST
# define PI2 PI / 2 //SOUTH
# define PI3 3 * PI / 2 //NORTH
# define DR 0.0174533
# define WIN_H 750
# define WIN_W 1024
# define RAYNR WIN_W

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
	t_arr 		map;
	size_t		width;			//starting from 1
	size_t		height;			//starting from 1
	t_direction	player_dir;
	size_t		player_x;		//arr_index
	size_t		player_y;		//arr_index
	char		*ea;
	char		*so;
	char		*we;
	char		*no;
	uint32_t	color_f;
	uint32_t	color_c;
	// t_ident ids;
}	t_data;

typedef struct s_map3d
{
	// mlx_image_t *map_3d[RAYNR];
	uint32_t	**buffer;
}	t_map3d;

typedef struct s_player
{
	mlx_t		*mlx;
	mlx_image_t *img;
	mlx_image_t *dir;
	mlx_texture_t	*textures[4];
	t_map3d		*map3d;
	float	px;
	float	py;
	float	pdx; //delta x
	float	pdy; //delta y
	float	pa; //angle
}	t_player;

typedef struct s_ray
{
	int		r;
	int		mx;
	int		my;
	int		mp;
	int		dof;
	float	rx;
	float	ry;
	float	ra;
	float	xo;
	float	yo;
	float	dist;
	
	float	disH;
	float	disV;
	float	hx;
	float	hy;
	float	vx;
	float	vy;
	t_direction wall;
	float	shade;
}	t_ray;

typedef struct	s_texture
{
	mlx_texture_t	*t;
	float	tx;
	float	ty;
	float	ty_off;
	float	ty_step;
	int		lineH;
	float	lineO;
}	t_texture;

void 		paint_image(mlx_image_t *img, int32_t color);
void		draw_rays_3d(t_player player, mlx_image_t *crash);
// uint32_t	get_texcolor(mlx_texture_t *t, uint32_t x, uint32_t y, float shade);
uint32_t	get_texcolor(mlx_texture_t *t, uint32_t x, uint32_t y);
int 		arr_create(t_arr *arr);
int 		arr_add(t_arr *arr, char *str);
char 		*arr_get(t_arr *arr, unsigned long index);
void 		arr_free(t_arr *arr);