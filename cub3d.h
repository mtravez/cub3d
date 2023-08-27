# include "lib/MLX42/include/MLX42/MLX42.h"
# include "lib/libft/libft.h"
# include <math.h>
# include <stdio.h>
# define BPP sizeof(int32_t)
# define MAPY 8
# define MAPX 8
# define MAPS 64
# define PINK 0xFAA0EFFF
# define SHADOW 0xB876B0FF
# define GROUND 0x000000FF
# define WALL 0xAFFAA0FF
# define PI 3.14159265359
# define PI2 PI / 2
# define PI3 3 * PI / 2
# define DR 0.0174533
# define RAYNR 60

typedef struct s_data
{
	char **map;
	int height;
	int width;
}	t_data;

typedef struct s_map3d
{
	mlx_image_t *map_3d[RAYNR];
}	t_map3d;

typedef struct s_player
{
	mlx_t		*mlx;
	mlx_image_t *img;
	mlx_image_t *dir;
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
}	t_ray;

void paint_image(mlx_image_t *img, int32_t color);
void	draw_rays_3d(t_player player, mlx_image_t *crash, t_map3d *map3d);