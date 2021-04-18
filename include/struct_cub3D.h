#ifndef STRUCT_CUB3D_H
# define STRUCT_CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../Libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <X11/X.h>
# include <X11/Xlib.h>
# include <math.h>

# define KRED  "\x1B[31m"
# define KGRN  "\x1B[32m"

# define RED_PIXEL 0xFF0000
# define GREEN_PIXEL 0x00FF00
# define BLUE_PIXEL 0x0000FF
# define GREY_PIXEL 0x808080
# define PINK_PIXEL 0xFD6C9E

# define ROTATE_LEFT_ARROW 65361
# define ROTATE_LEFT_Q 101
# define ROTATE_RIGHT_ARROW 65363
# define ROTATE_RIGHT_E 113
# define FORWARD_W 119
# define BACK_S 115
# define RIGHT_D 100
# define LEFT_A 97

typedef struct		s_perso {
	float		position_x;
	float		position_y;
	float		dirx;
	float		diry;
	float		angle;
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
	int				nb_sprites;
	int				nb_sprite_1;
	int				nb_sprite_2;
	t_colour		floor_colour;
	char			*north_texture;
	char			*south_texture;
	char			*west_texture;
	char			*east_texture;
	t_perso			perso;
}					t_param;

typedef struct		s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_lenght;
	int		endian;
	int		width;
	int		height;
}					t_img;

typedef struct		s_ray
{
	double		pos_x; /* position x du joueur */
	double		pos_y; /* position y du joueur */
	double		dir_x; /* vecteur de direction (commence à -1 pour N,
						  1 pour S, 0 sinon) */
	double		dir_y; /* vecteur de direction (commence à -1 pour W, 1 pour E,
						  0 sinon) */
	double		plan_x; /* vecteur du plan (commence à 0.66 pour E, -0.66 pour
						   W, 0 sinon) */
	double		plan_y; /* vecteur du plan (commence à 0.66 pour N, -0.66 pour
						   S, 0 sinon) */
	double		ray_dirx; /* calcul de direction x du rayon */
	double		ray_diry; /* calcul de direction y du rayon */
	double		camera_x; /* point x sur la plan camera : Gauche ecran = -1,
							 milieu = 0, droite = 1 */
	int			map_x; /* coordonée x du carré dans lequel est pos */
	int			map_y; /* coordonnée y du carré dans lequel est pos */
	double		side_distx; /* distance que le rayon parcours jusqu'au premier
							   point d'intersection vertical (=un coté x) */
	double		side_disty; /* distance que le rayon parcours jusqu'au premier
							   point d'intersection horizontal (= un coté y) */
	double		delta_distx; /* distance que rayon parcours entre chaque point
								d'intersection vertical */
	double		delta_disty; /* distance que le rayon parcours entre chaque
								point d'intersection horizontal */
	int			step_x; /* -1 si doit sauter un carre dans direction x negative,
						   1 dans la direction x positive */
	int			step_y; /* -1 si doit sauter un carre dans la direction y
						   negative, 1 dans la direction y positive */
	int			hit; /* 1 si un mur a ete touche, 0 sinon */
	int			side; /* 0 si c'est un cote x qui est touche (vertical),
						 1 si un cote y (horizontal) */
	double		perp_wall_dist; /* distance du joueur au mur */
	int			line_height; /* hauteur de la ligne a dessiner */
	int			draw_start; /* position de debut ou il faut dessiner */
	int			draw_end; /* position de fin ou il faut dessiner */
	int			x; /* permet de parcourir tous les rayons */
}					t_ray;

typedef struct		s_sprite
{
	int		draw_start_x;
	int		draw_start_y;
	int		draw_end_x;
	int		draw_end_y;
	double	pos_x;
	double	pos_y;
	int		height;
	int		width;
	double	*distance;
	double	*z_buffer;
	int		*order;
	t_img	img;

}					t_sprite;

typedef struct		s_texture
{
	double			wallx; // valeur où le mur a été touché : coordonnée y si side == 0, coordonnée x si side == 1
	int			text_dir; // direction NO, S, EA, WE de la texture
	int			x; // coordonnee x de la texture
	int			y; // coordonnee y de la texture
	double			step; // de combien augmenter les coordonnées de la texture pour chaque pixel
	double		position; // coordonnee de depart
	double		shade;
	int			*color;
}					t_texture;

typedef	struct		s_bonus
{
	int			life;
}				t_bonus;

typedef struct		s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
	t_param		param;
	t_ray		ray;
	t_texture	texture;
	t_img		tab_texture[6];
	t_sprite 	sprite;
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
