/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 15:11:39 by slescure          #+#    #+#             */
/*   Updated: 2021/02/05 16:46:23 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		calculate_nb_chains(char *str)
{
	int result;
	int i;

	i = 0;
	result = 0;
	while (str[i] != '\0')
	{
		i++;
		if (str[i] == '\n')
			result++;
	}
	return (result);
}

int		ft_biggest_line_len(char *str)
{
	int i;
	int j;
	int result;

	j = 0;
	i = 0;
	result = 1;
	while (str[i] != '\0')
	{
		while (str[i] != '\n')
		{
			i++;
			j++;
		}
		if (j > result)
			result = j;
		j = 0;
		i++;
	}
	result++;
	return (result);
}

char	*only_map(char *str)
{
	int		i;
	int		j;
	int		max_length;
	char	*map;

	i = 0;
	j = 0;
	while (str[i] != '\n' || str[i + 2] != '\n')
		i++;
	while (str[i] == '\n')
		i++;
	j = calculate_nb_chains(str);
	max_length = ft_biggest_line_len(str);
	if (!(map = malloc(sizeof(char) * j * max_length)))
		return (NULL);
	j = 0;
	while (str[i] != '\0')
	{
		map[j] = str[i];
		i++;
		j++;
	}
	map[j] = '\0';
	return (map);
}

char	**creation_tableau_map(char *str, char **liste, int max_length)
{
	int largeur;
	int longueur;
	int i;

	largeur = 0;
	i = -1;
	while (str[++i] != '\0')
	{
		longueur = 0;
		while (str[i] != '\n')
		{
			while (str[i] == ' ')
			{
				liste[largeur][longueur++] = '5';
				i++;
			}
			liste[largeur][longueur++] = str[i];
			i++;
			if ((str[i] == '\n') && (longueur < max_length - 1))
			{
				while (longueur < max_length - 1)
					liste[largeur][longueur++] = '5';
			}
		}
		largeur++;
	}
	return (liste);
}

int		parsing_map(char *str)
{
	int		largeur;
	int		i;
	int		max_length;
	char	**liste;

	i = 0;
	str = only_map(str);
	largeur = calculate_nb_chains(str);
	max_length = ft_biggest_line_len(str);
	if (!(liste = malloc(sizeof(char*) * largeur)))
		return (-1);
	while (i < largeur)
	{
		if (!(liste[i] = malloc(sizeof(char**) * max_length)))
			return (-1);
		i++;
	}
	liste = creation_tableau_map(str, liste, max_length);
	verification_map(liste, largeur, max_length);
	return (0);
}
