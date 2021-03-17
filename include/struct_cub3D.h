#ifndef STRUCT_CUB3D_H
# define STRUCT_CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../Libft/get_next_line/get_next_line.h"
# include "../Libft/libft.h"
# include "cub3D.h"

# define KRED  "\x1B[31m"
# define KGRN  "\x1B[32m"

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

#endif
