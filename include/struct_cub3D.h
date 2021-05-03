#ifndef STRUCT_CUB3D_H
# define STRUCT_CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include <X11/Xlib.h>
# include <math.h>
# include <time.h>

# define KRED  "\x1B[31m"
# define KGRN  "\x1B[32m"

# define RED_PIXEL 0xFF0000
# define GREEN_PIXEL 0x00FF00
# define BLUE_PIXEL 0x0000FF
# define GREY_PIXEL 0x808080
# define PINK_PIXEL 0xFD6C9E

# define ROTATE_LEFT_ARROW 65363
# define ROTATE_LEFT_Q 101
# define ROTATE_RIGHT_ARROW 65361
# define ROTATE_RIGHT_E 113
# define FORWARD_W 119
# define SPEED_ARROW 65364
# define NORMAL_SPACE 32
# define SLOW_ARROW 65362
# define BACK_S 115
# define RIGHT_D 100
# define LEFT_A 97

typedef struct		s_perso {
	float		position_x;
	float		position_y;
	float		dirx;
	float		diry;
	float		angle;
	float		speed;
	char		orientation;
}					t_perso;

typedef struct		s_colour {
	int	red;
	int	green;
	int	blue;
}					t_colour;

typedef struct		s_resolution {
	int axe_x;
	int axe_y;
}					t_resolution;

typedef struct		s_map {
	char			**tab_map;
	char			*map;
	int				nb_lines;
	int				max_length;
}					t_map;

typedef struct		s_param {
	char			*file;
	t_map			map;
	t_colour		ceiling_colour;
	t_resolution	resolution;
	char			*sprite_1;
	char			*sprite_2;
	int				nb_lines_params;
	int				nb_sprites;
	t_colour		floor_colour;
	char			*north_texture;
	char			*south_texture;
	char			*west_texture;
	char			*east_texture;
	char			*ceiling_texture;
	char			*floor_texture;
	t_perso			perso;
	int				bonus;
}					t_param;

typedef struct		s_sound
{
	clock_t			last_start_song;
}					t_sound;

typedef struct		s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		width;
	int		height;
	t_sound	*sound;
}					t_img;

typedef struct		s_ray
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plan_x;
	double		plan_y;
	double		ray_dirx;
	double		ray_diry;
	double		camera_x;
	int			map_x;
	int			map_y;
	double		side_distx;
	double		side_disty;
	double		delta_distx;
	double		delta_disty;
	int			step_x;
	int			step_y;
	int			hit;
	int			side;
	double		perp_wall_dist;
	int			line_height;
	int			draw_start;
	int			draw_end;
	int			x;
}					t_ray;

typedef struct		s_sprite
{
	double	sprite_x;
	double	sprite_y;
	int		draw_start_x;
	int		draw_start_y;
	int		draw_end_x;
	int		draw_end_y;
	double	pos_x;
	double	pos_y;
	int		height;
	int		width;
	double	transform_x;
	double	transform_y;
	double	dist;
	int		screen;
	double	*z_buffer;
	int		order;
	double	invdet;
	char	type;
	t_img	img;

}					t_sprite;

typedef struct		s_texture
{
	double	wallx;
	int		text_dir;
	int		x;
	int		y;
	double	step;
	double	position;
	double	shade;
	int		*color;
}					t_texture;

typedef	struct		s_bonus
{
	int			life;
	t_img		tab_life[4];
}					t_bonus;

typedef struct		s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
	t_param		param;
	t_ray		ray;
	t_texture	texture;
	t_img		tab_texture[6];
	t_img		sprite1;
	t_img		sprite2;
	t_sprite	*tab_sprite;
	t_bonus		bonus;
}					t_data;

typedef struct		s_rect
{
	int		x;
	int		y;
	int		width;
	int		height;
	int		color;
}					t_rect;

#endif
