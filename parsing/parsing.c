/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 14:07:11 by slescure          #+#    #+#             */
/*   Updated: 2021/02/09 15:50:42 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		gestion_erreur(int argc, char **argv)
{
	int 	i;
	char 	*s1;

	s1 = "--save";
	i = 0;
	if (argc != 2 && argc != 3) //verification nombre d'arguments
    {
        perror("ERROR : wrong number of arguments");
        exit(0);
    }
	if (argc == 3 && (ft_is_string(argv[2], s1) == 0)) //verification "--save"
	{
		perror("ERROR : wrong 3rd arguemnt");
		exit(0);
	}
	file_is_cub(argv[1]);
	return (0);
}

int			file_is_cub(char *str)
{
	int i;

	i = 0;
	while (str[i] != '.') //verification fichier format .cub
		i++;
	i++;
	if (str[i] == 'c' && str[i+1] == 'u' && str[i+2] == 'b'
		&& str[i+3] == '\0')
		return (1);
	else
	{
		perror("ERROR : wrong format of file");
		exit(0);
	}
	return (0);
}

int			ft_is_string(char *s1, char *s2)
{
	int i;
	size_t n;

	i = 0;
	n = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] == s2[i])
			n++;
		i++;
	}
	if (n == ft_strlen(s1))
		return (1);
	return (0);
}

int		read_map(int fd, char *str, char *map)
{
	int r;

	r = 1;
	while ((r = read(fd, str, 10)) > 0)
    {
        str[r] = '\0';
        map = ft_strjoin(map, str);
    }
	parametres_map(map);
	parsing_map(map);
	free(map);
	free(str);
	return (0);
}

int     main(int argc, char **argv)
{
    char *str;
    char *map;
    int fd;

    map = "";
    if (!(str = malloc(sizeof(char) * 11)))
        return (-1);
    fd = open(argv[1], O_RDONLY);
	gestion_erreur(argc, argv);
    read_map(fd, str, map);
    return (0);
}
