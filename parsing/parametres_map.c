/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parametres_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:21:58 by slescure          #+#    #+#             */
/*   Updated: 2021/02/09 17:20:38 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*only_parameters_in_map(char *str) // good
{
	int i;
	int n;
	char *map;

	i = 0;
	n = 0;
	while ((str[i] != '\n' || str[i + 1] != '1')
		&& (str[i] != '\n' || str[i + 1] != ' '))
	{
		i++;
		n++;
	}
	if (!(map = malloc(sizeof(char) * n + 1)))
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
	while (str[i] != '\0')
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
		i++;
		largeur++;
	}
	return (liste);
}

int		gerer_param(char *str)
{
	int i;

	i = 0;
	if (str[0] == 'C')
		colour_params(str);
	if (str[0] == 'R')
		resolution_param(str);
	if (str[0] == 'S' && str[1] == ' ')
		recuperation_adresse_param(str);
	if (str[0] == 'F')
		colour_params(str);
	if (str[0] == 'N' && str[1] == 'O')
		printf("north_texture_param\n");
	if (str[0] == 'S' && str[1] == 'O')
		printf("south_texture_param\n");
	if (str[0] == 'E' && str[1] == 'A')
		printf("east_texture_param\n");
	if (str[0] == 'W' && str[1] == 'E')
		printf("west_texture_param\n");
	return (0);
}

int		verification_all_para(char **tab, int largeur)
{
	int i;

	i = 0;
	while (i < largeur)
	{
		gerer_param(tab[i]);
		i++;
	}
	return (0);
}

int		parametres_map(char *str) // good
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
	if (!(tab_param = malloc(sizeof(char*) * largeur + 1)))
		return (-1);
	while (i < largeur)
	{
		if (!(tab_param[i] = malloc(sizeof(char**) * max_length + 1)))
			return (-1);
		i++;
	}
	tab_param = creation_tableau_param(map, tab_param);
	i = 0;
	while (i < largeur)
	{
		printf("tab_param[%i] = %s\n", i, tab_param[i]);
		i++;
	}
	verification_all_para(tab_param, largeur);
	return (0);
}
