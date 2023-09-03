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

typedef struct s_data
{
	char **map;
	int height;
	int width;
	t_direction	player_dir;
	int	player_x;
	int player_y;
	uint32_t	color_f;
	uint32_t	color_c;
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

void paint_image(mlx_image_t *img, int32_t color);
void	draw_rays_3d(t_player player, mlx_image_t *crash);
// uint32_t	get_texcolor(mlx_texture_t *t, uint32_t x, uint32_t y, float shade);
uint32_t	get_texcolor(mlx_texture_t *t, uint32_t x, uint32_t y);