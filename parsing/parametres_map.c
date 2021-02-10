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

void 	impression_params(t_param *param)
{
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

char	**creation_tableau_param(char *str, char **liste) // good
{
	int i;
	int largeur;
	int longueur;

	i = 0;
	largeur = 0;
	longueur = 0;
	while (str[i] != '\0' && largeur < 8)
	{
		longueur = 0;
		while (str[i] == '\n' && str[i] != '\0')
			i++;
		while (str[i] != '\n' && str[i] != '\0')
		{
			liste[largeur][longueur] = str[i];
			i++;
			longueur++;
		}
			printf("||||||  %d %s||||||\n",largeur, liste[largeur]);
		liste[largeur][longueur] = '\0';
		if (str[i] != 0)
			i++;
		largeur++;
	}
	return (liste);
}

int		gerer_param(char *str, t_param *param)
{
	int i;

	i = 0;
	if (str[0] == 'C')
		colour_params_colour(str, param);
	if (str[0] == 'R')
		resolution_param(str, param);
	if (str[0] == 'S' && str[1] == ' ')
		param->sprite = recuperation_adresse_param(str);
	if (str[0] == 'F')
		colour_params_ground(str, param);
	if (str[0] == 'N' && str[1] == 'O')
	{
		if (!(param->north_texture = malloc(sizeof(char) * ft_strlen(str))))
			return (-1);
		param->north_texture = recuperation_adresse_param(str);
	}
	if (str[0] == 'S' && str[1] == 'O')
	{
		if (!(param->south_texture = malloc(sizeof(char) * ft_strlen(str))))
			return (-1);
		param->south_texture = recuperation_adresse_param(str);
	}
	if (str[0] == 'E' && str[1] == 'A')
	{
		if (!(param->east_texture = malloc(sizeof(char) * ft_strlen(str))))
			return (-1);
		param->east_texture = recuperation_adresse_param(str);
	}
	if (str[0] == 'W' && str[1] == 'E')
	{
		if (!(param->west_texture = malloc(sizeof(char) * ft_strlen(str))))
			return (-1);
		param->west_texture = recuperation_adresse_param(str);
	}
	return (0);
}

int		verification_all_para(char **tab, int largeur, t_param *param)
{
	int i;

	i = 0;
	while (i < largeur)
	{
		gerer_param(tab[i], param);
		i++;
	}
	impression_params(param);
	return (0);
}

int		parametres_map(char *str, t_param *param) // good
{
	char *map;
	char **tab_param;
	int largeur;
	int max_length;
	int i;

	i = 0;
	map = only_parameters_in_map(str);
	largeur = calculate_nb_chains(map);
	max_length = ft_biggest_line_len(map);
	if (largeur != 8)
	{
		perror("ERROR : wrong number of parameters"); // permet de savoir s'il y en a 8
		exit(0);
	}
	if (!(tab_param = malloc(sizeof(char*) * (largeur + 1))))
		return (-1);
	while (i < largeur)
	{
		if (!(tab_param[i] = malloc(sizeof(char) * (max_length + 1))))
			return (-1);
		i++;
	}
	tab_param = creation_tableau_param(map, tab_param);
	i = 0;
	while (i < largeur)
	{
		//printf("tab_param[%i] = %s\n", i, tab_param[i]);
		i++;
	}
	verification_all_para(tab_param, largeur, param);
	return (0);
}
