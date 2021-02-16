/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parametres_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:21:58 by slescure          #+#    #+#             */
/*   Updated: 2021/02/09 19:32:22 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void 	free_address_params(t_param *param)
{
	free(param->sprite);
	free(param->north_texture);
	free(param->south_texture);
	free(param->east_texture);
	free(param->west_texture);
}

void 	print_params(t_param *param)
{
	printf("fichier = %s\n", param->file);
	printf("map = %s\n", param->map.map[0]);
	printf("nb_lines = %i\n", param->map.nb_lines);
	printf("color_red : %i\n", param->colour.red);
	printf("color_green : %i\n", param->colour.green);
	printf("color_blue : %i\n", param->colour.blue);
	printf("color_ground_red : %i\n", param->ground_colour.red);
	printf("color_ground_green : %i\n", param->ground_colour.green);
	printf("color_ground_blue : %i\n", param->ground_colour.blue);
	printf("resolution_x : %i\n", param->resolution.axe_x);
	printf("resolution_y : %i\n", param->resolution.axe_y);
	printf("addrese sprite : %s\n", param->sprite);
	printf("addrese north : %s\n", param->north_texture);
	printf("addrese south : %s\n", param->south_texture);
	printf("addrese east : %s\n", param->east_texture);
	printf("addrese west : %s\n", param->west_texture);
	printf("position perso x = %i\n", param->perso.position_x);
	printf("position perso y = %i\n", param->perso.position_y);
	printf("orientation perso = %c\n", param->perso.orientation);
}

char	*only_parameters_in_map(char *str) // good
{
	int i;
	char *map;

	i = 0;
	while ((str[i] != '\n' || str[i + 1] != '1')
		&& (str[i] != '\n' || str[i + 1] != ' '))
		i++;
	if (!(map = malloc(sizeof(char) * i + 1)))
		return (NULL);
	i = 0;
	while ((str[i] != '\n' || str[i + 1] != '1')
		&& (str[i] != '\n' || str[i + 1] != ' '))
	{
		map[i] = str[i];
		i++;
	}
	map[i] = '\0';
	return (map);
}

char	**creation_table_param(char *str, char **map) // good
{
	int i;
	int nb_lines;
	int length;

	i = 0;
	nb_lines = 0;
	length = 0;
	while (str[i] != '\0' && nb_lines < 8)
	{
		length = 0;
		while (str[i] == '\n' && str[i] != '\0')
			i++;
		while (str[i] != '\n' && str[i] != '\0')
		{
			map[nb_lines][length] = str[i];
			i++;
			length++;
		}
		map[nb_lines][length] = '\0';
		if (str[i] != 0)
			i++;
		nb_lines++;
	}
	return (map);
}

int		manage_param(char *str, t_param *param)
{
	int i;

	i = 0;
	if (str[0] == 'C')
		colour_params_colour(str, param);
	if (str[0] == 'R')
		resolution_param(str, param);
	if (str[0] == 'S' && str[1] == ' ')
		param->sprite = save_address_param(str);
	if (str[0] == 'F')
		colour_params_ground(str, param);
	if (str[0] == 'N' && str[1] == 'O')
		param->north_texture = save_address_param(str);
	if (str[0] == 'S' && str[1] == 'O')
		param->south_texture = save_address_param(str);
	if (str[0] == 'E' && str[1] == 'A')
		param->east_texture = save_address_param(str);
	if (str[0] == 'W' && str[1] == 'E')
		param->west_texture = save_address_param(str);
	return (0);
}

int		check_all_para(char **tab, int nb_lines, t_param *param)
{
	int i;

	i = -1;
	while (++i < nb_lines)
		manage_param(tab[i], param);
	if (param->colour.red == -10 || param->colour.green == -10 ||
		param->colour.blue == -10 || param->ground_colour.red == -10 ||
		param->ground_colour.green == -10 || param->ground_colour.blue == -10)
	{
		perror ("ERROR : missing colour");
		exit (0);
	}
	if (param->resolution.axe_x == -10 || param->resolution.axe_y == -10)
	{
		perror("ERROR : missing resolution");
		exit (0);
	}
	if (param->sprite == NULL || param->north_texture == NULL ||
		param->south_texture == NULL || param->east_texture == NULL ||
		param->west_texture == NULL)
	{
		perror("ERROR : missing texture or sprite");
		exit (0);
	}
	return (0);
}

int		parameters_map(char *str, t_param *param) // good
{
	char *map;
	char **tab_param;
	int nb_lines;
	int max_length;
	int i;

	i = 0;
	map = only_parameters_in_map(str);
	nb_lines = calculate_nb_chains(map);
	max_length = ft_biggest_line_len(map);
	if (nb_lines != 8)
	{
		perror("ERROR : wrong number of parameters"); // permet de savoir s'il y en a 8
		exit(0);
	}
	if (!(tab_param = malloc(sizeof(char*) * (nb_lines + 1))))
		return (-1);
	while (i < nb_lines)
	{
		if (!(tab_param[i] = malloc(sizeof(char) * (max_length + 1))))
			return (-1);
		i++;
	}
	tab_param = creation_table_param(map, tab_param);
	i = 0;
//	while (i < nb_lines)
//	{
//		printf("tab_param[%i] = %s\n", i, tab_param[i]);
//		i++;
//	}
	check_all_para(tab_param, nb_lines, param);
	printf("PARAMETERS : [OK]\n");
	print_params(param);
	i = 0;
	while (i < nb_lines)
	{
		free(tab_param[i]);
		i++;
	}
	free(tab_param);
	free(map);
	return (0);
}
