#ifndef CUB3D_H
# define CUB3D_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

size_t	ft_strlen(char *str);
int     calculate_nb_chains(char *str);
int     ft_biggest_line_len(char *str);
int     parsing(char *str);
char     *only_map(char *str);
int     creation_tableau_map(char *str);
char     **recup_map(char **str, int largeur, int longueur);
int     verif_walls_and_symbols(char *str, int longueur);

#endif
