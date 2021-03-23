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

# define KRED  "\x1B[31m"
# define KGRN  "\x1B[32m"

#define RED_PIXEL 0xFF0000
#define GREEN_PIXEL 0x00FF00
#define BLUE_PIXEL 0x0000FF

#define ROTATE_LEFT 65361
#define ROTATE_RIGHT 65363
#define FORWARD_W_Z 119
#define BACK_S_S 115
#define RIGHT_D_D 100
#define LEFT_A_Q 97

typedef struct	s_perso {
	int		position_x;
	int		position_y;
	char	orientation;
}	t_perso ;

typedef struct	s_colour {
	int	red;
	int	green;
	int	blue;
}	t_colour ;

typedef struct	s_resolution {
	int axe_x;
	int axe_y;
}	t_resolution ;

typedef struct	s_map {
	char **map;
	int	nb_lines;
	int	max_length;
}	t_map ;

typedef struct	s_param {
	char			*file;
	t_map			map;
	t_colour		colour;
	t_resolution	resolution;
	char			*sprite;
	t_colour		ground_colour;
	char			*north_texture;
	char			*south_texture;
	char			*west_texture;
	char			*east_texture;
	t_perso			perso;
}	t_param ;

typedef struct s_rect
{
	int	x;
	int	y;
	int	width;
	int	height;
	int	color;
}		t_rect;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_lenght;
	int		endian;
	t_rect	rect;
}			t_img;

typedef struct	s_ray
{
   double		posx; //position x du joueur
   double		posy; //position y du joueur
   double		dirx; //vecteur de direction (commence à -1 pour N, 1 pour S, 0 sinon)
   double		diry; //vecteur de direction (commence à -1 pour W, 1 pour E, 0 sinon)
   double		planx; //vecteur du plan (commence à 0.66 pour E, -0.66 pour W, 0 sinon)
   double		plany; //vecteur du plan (commence à 0.66 pour N, -0.66 pour S, 0 sinon)
   double		raydirx; //calcul de direction x du rayon
   double		raydiry; //calcul de direction y du rayon
   double		camerax; //point x sur la plan camera : Gauche ecran = -1, milieu = 0, droite = 1
   int			mapx; // coordonée x du carré dans lequel est pos
   int			mapy; // coordonnée y du carré dans lequel est pos
   double		sidedistx; //distance que le rayon parcours jusqu'au premier point d'intersection vertical (=un coté x)
   double		sidedisty; //distance que le rayon parcours jusqu'au premier point d'intersection horizontal (= un coté y)
   double		deltadistx; //distance que rayon parcours entre chaque point d'intersection vertical
   double		deltadisty; //distance que le rayon parcours entre chaque point d'intersection horizontal
   int			stepx; // -1 si doit sauter un carre dans direction x negative, 1 dans la direction x positive
   int			stepy; // -1 si doit sauter un carre dans la direction y negative, 1 dans la direction y positive
   int			hit; // 1 si un mur a ete touche, 0 sinon
   int			side; // 0 si c'est un cote x qui est touche (vertical), 1 si un cote y (horizontal)
   double		perpwalldist; // distance du joueur au mur
   int			lineheight; //hauteur de la ligne a dessiner
   int			drawstart; //position de debut ou il faut dessiner
   int			drawend; //position de fin ou il faut dessiner
   int			x; //permet de parcourir tous les rayons
}	t_ray ;

typedef struct s_data
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	img;
	t_param	param;
	t_ray	ray;
}			t_data;

#endif
