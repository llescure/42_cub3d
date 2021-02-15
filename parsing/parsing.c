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

int		manage_errors(int argc, char **argv)
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
	if (str[i] == 'c' && str[i + 1] == 'u' && str[i + 2] == 'b'
		&& str[i + 3] == '\0')
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

int		read_map(int fd, char *str, char *map, t_param *param)
{
	int		reader;
	char	*tmp;

	reader = 1;
	while ((reader = read(fd, str, 1)) > 0)
    {
        str[reader] = '\0';
		tmp = map;
        map = ft_strjoin(tmp, str);
		free(tmp);
    }
	parameters_map(map, param);
	parsing_map(map, param);
	free(map);
	free(str);
	return (0);
}

t_param	initialize_structure(t_param *param)
{
	param->colour.red = -10;
	param->colour.blue = -10;
	param->colour.green = -10;
	param->ground_colour.red = -10;
	param->ground_colour.blue = -10;
	param->ground_colour.green = -10;
	param->resolution.axe_x = -10;
	param->resolution.axe_y = -10;
	param->sprite = NULL;
	param->north_texture = NULL;
	param->south_texture = NULL;
	param->west_texture = NULL;
	param->east_texture = NULL;
	param->perso.orientation = 0;
	param->perso.position_x = -10;
	param->perso.position_y = -10;
	return (*param);
}

int     main(int argc, char **argv)
{
    char *str;
    char *map;
    int fd;
	t_param param;

	if (!(map = malloc(sizeof(char) * 2)))
		return (-1);
	map[0] = 0;
    if (!(str = malloc(sizeof(char) * 2)))
        return (-1);
	initialize_structure(&param);
	fd = open(argv[1], O_RDONLY);
	manage_errors(argc, argv);
    read_map(fd, str, map, &param);
	while (1)
	    ;
    return (0);
}
