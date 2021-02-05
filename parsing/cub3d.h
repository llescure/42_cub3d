/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 16:18:00 by slescure          #+#    #+#             */
/*   Updated: 2021/02/05 16:34:48 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

size_t		ft_strlen(char *str);
char		*ft_strjoin(char *s1, char *s2);
int			calculate_nb_chains(char *str);
int			ft_biggest_line_len(char *str);
char		*only_map(char *str);
char		**recup_map(char **str, int largeur, int longueur);
char		**creation_tableau_map(char *map, char **liste, int max_length);
int			verif_walls_extremite_and_symbols(char *str, int longueur);
int			verif_holes_walls(char **map, int largeur, int longueur);
int			verif_first_last_string_map(char *str);
int			verification_map(char **liste, int largeur, int max_length);
int			parsing_map(char *str);

#endif
