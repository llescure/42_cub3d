/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 15:23:17 by slescure          #+#    #+#             */
/*   Updated: 2021/01/08 17:15:42 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

int		get_next_line(int fd, char **line);
int		initialisation(int fd, char **save, char **line, char **buf);
int		ret(char **save, char **line, char **tmp, int r);
size_t	ft_strlen(char *s);
char	*ft_strchr(char *str, int c);
char	*get_rest(char *str);
char	*ft_strjoin(char *s1, char *s2);
char	*get_line(char *str);

#endif
