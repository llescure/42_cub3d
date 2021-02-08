/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parametres_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 15:21:58 by slescure          #+#    #+#             */
/*   Updated: 2021/02/08 17:23:48 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*only_parameters(char *str)
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

char	**creation_tableau_param(char *str, char **liste)
{
	int i;
	int largeur;
	int longueur;

	i = 0;
	largeur = 0;
	longueur = 0;
	printf("str = %s\n", str);
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

int		parametres_map(char *str)
{
	char *map;
	char **tab_param;
	int largeur;
	int max_length;
	int i;

	i = 0;
	map = only_parameters(str);
	largeur = calculate_nb_chains(map);
	max_length = ft_biggest_line_len(map);
	printf("largeur = %i\n", largeur);
	printf("max_length = %i\n", max_length);
	if (largeur != 8)
	{
		perror("ERROR : wrong number of parameters");
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
	printf("tab_param[0] = %s\n", tab_param[0]);
	return (0);
}
