# include "lib/MLX42/include/MLX42/MLX42.h"
# include "lib/libft/libft.h"
# include <math.h>
# include <stdio.h>
# define BPP sizeof(int32_t)
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
}	t_data;

typedef struct s_map3d
{
	// mlx_image_t *map_3d[RAYNR];
	uint32_t	**buffer;
}	t_map3d;

typedef struct s_player
{
	mlx_t		*mlx; //set at parsing for the textures
	mlx_image_t *img; //set at main
	mlx_texture_t	*textures[4];	//set at parsing, use enum for position (only allow square textures, please)
	t_map3d		*map3d;	//set at runtime
	t_data	*data;
	float	px;	//set at parsing
	float	py;	//set at parsing
	float	pdx; //delta x (set when keypress)
	float	pdy; //delta y (set when keypress)
	float	pa; //angle (set at parsing) (PI3 = NORTH, 0 = EAST, PI2 = SOUTH, PI = WEST)
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
void	draw_rays_3d(t_player player);
// uint32_t	get_texcolor(mlx_texture_t *t, uint32_t x, uint32_t y, float shade);
uint32_t	get_texcolor(mlx_texture_t *t, uint32_t x, uint32_t y);
int 		arr_create(t_arr *arr);
int 		arr_add(t_arr *arr, char *str);
char 		*arr_get(t_arr *arr, unsigned long index);
void 		arr_free(t_arr *arr);
void		play(t_data data);

// PARSER
int			handle_input(int argc, char**argv, int *fd);
void		init_data(t_data *data);
int			parser(t_data *data, char **argv, int fd);
int			check_file_type(char *argv);
int			get_identifiers(t_data *data, int fd);
int			get_map(t_data *data, int fd);
int			validate_map(t_data *data);
int			check_player(t_data *data);
int			is_player_pos_set(t_data *data);

void		free_2d(char **str, int i);
void 		free_textures(t_data *data);
int			str_eq(const char *s1, const char *s2);
