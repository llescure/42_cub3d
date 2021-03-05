/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 16:18:00 by slescure          #+#    #+#             */
/*   Updated: 2021/03/04 12:36:51 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include "../Libft/get_next_line/get_next_line.h"

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

int			sorting_map(char *map_map, t_param *param);

size_t		ft_strlen(char *str);
char		**ft_split(char const *s, char c);
char		*ft_strjoin(char *s1, char *s2);
int			ft_isalpha(int a);
int			ft_atoi_cub3d(char *str, int i);
char    	**malloc_tab(t_param *param);

int			ft_is_string(char *s1, char *s2);
int			manage_errors(int argc, char **argv);
int			file_is_cub(char *str);
t_param		initialize_structure(t_param *param, char *argv);
int			parsing_map(char *str, t_param *param);

int			calculate_nb_chains(char *str);
int			ft_biggest_line_len(char *str);
int			read_map(int fd, char *str, char *map, t_param *param);
int			read_next_line(char **tab_map, char **tab_param, char **line, int fd);
int			check_map(char **map, int nb_lines, int max_length, t_param *param);
char		*only_map(char *str, t_param *param);
char		**save_map(char **str, int nb_lines, int length);
char		**creation_table_map(char **str, t_param *param);
int			check_end_walls(char *str, int length);
char     	*check_space_in_map(char *str);
int			check_symbols(char *str);
int     	check_void_line_map(char *str);
int			check_holes_walls(char **map, int nb_lines, int length);
int			check_first_last_string_map(char *str);

int			check_all_para(t_param *param, char **tab_param);
int			perso_orientation_position(char *map, t_param *param, int position);
int     	manage_perso(char **map, t_param *param);
int			manage_param(char *str, t_param *param);
int			parameters_map(char *str, t_param *param);
int     	only_params(char *str);

char		*save_param_numbers(char *str, char *res, int i);
int			resolution_param(char *str, t_param *param);
void 		print_params(t_param *param);
char		*save_address_param(char *str);
int			colour_params_colour(char *str, t_param *param);
int			colour_params_ground(char *str, t_param *param);
void		free_address_params(t_param *params);


#endif
