/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 15:11:39 by slescure          #+#    #+#             */
/*   Updated: 2021/02/09 13:55:23 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		calculate_nb_chains(char *str)
{
	int result;
	int i;

	i = 0;
	result = 0;
	while (str[i] == '\n')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] == '\n' && str[i + 1] != '\n')
			result++;
		i++;
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
	while ((str[i] != '\n' || str[i + 1] != '1')
		&& (str[i] != '\n' || str[i + 1] != ' '))
		i++;
	while (str[i] == '\n')
		i++;
	j = calculate_nb_chains(str);
	max_length = ft_biggest_line_len(str);
	if (!(map = malloc(sizeof(char) * j * max_length)))
		return (NULL);
	j = 0;
	while (str[i] != '\0')
		map[j++] = str[i++];
	map[j] = '\0';
	return (map);
}

char	**creation_table_map(char *str, char **map, int max_length)
{
	int nb_lines;
	int length;
	int i;

	nb_lines = 0;
	i = -1;
	while (str[++i] != '\0')
	{
		length = 0;
		while (str[i] != '\n')
		{
			while (str[i] == ' ')
			{
				map[nb_lines][length++] = '5';
				i++;
			}
			map[nb_lines][length++] = str[i];
			i++;
			if ((str[i] == '\n') && (length < max_length - 1))
			{
				while (length < max_length - 1)
					map[nb_lines][length++] = '5';
			}
		}
		nb_lines++;
	}
	return (map);
}

int		parsing_map(char *str, t_param *param)
{
	int		nb_lines;
	int		i;
	int		max_length;
	char	**map;

	i = 0;
	str = only_map(str);
	nb_lines = calculate_nb_chains(str);
	max_length = ft_biggest_line_len(str);
	if (!(map = malloc(sizeof(char*) * nb_lines + 1)))
		return (-1);
	while (i < nb_lines)
	{
		if (!(map[i] = malloc(sizeof(char**) * max_length)))
			return (-1);
		i++;
	}
	map = creation_table_map(str, map, max_length);
	i = 0;
//	while (i < nb_lines)
//	{
//		printf("map[%i] = %s\n", i, map[i]);
//		i++;
//	}
	check_map(map, nb_lines, max_length, param);
	return (0);
}
