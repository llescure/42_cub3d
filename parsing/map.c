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
		printf("map[%i] = %s\n", nb_lines, map[nb_lines]);
		nb_lines++;
	}
	return (map);
}

int		tri_map(char *map_map, t_param *param)
{
	int i;
	int j;
//	int nb_lines;
//	int max_length;
	int fd;
	int ret;
	char **tab_param;
	char **tab_map;
	char *line;

	i = 0;
	j = 0;
	ret =  1;
	line = NULL;
	fd = open(param->file, O_RDONLY);
	if (!(tab_param = malloc(sizeof(char*) * 8)))
		return (-1);
	if (!(tab_map = malloc(sizeof(char*) * calculate_nb_chains(map_map))))
	 	return (-1);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (line[0] == 'C' || line[0] == 'R' || line[0] == 'S' || line[0] == 'F'
			|| line[0] == 'E' || line[0] == 'W' || line[0] == 'N')
		{
			tab_param[i] = line;
			i++;
		}
		if (line[0] == ' ' || line[0] == '1')
		{
			tab_map[j] = line;
			j++;
		}
	}
	i = 0;
	while (i < j)
	{
		tab_map = creation_table_map(tab_map[i], param->map.max_length); // remplacer par des '5' dans espace
		i++;
	}
//	i = 0;
//	j = 0;
//	while (j < calculate_nb_chains(map_map))
//	{
//		printf("map[%i] = %s\n", j, tab_map[j]);
//		j++;
//	}
//	while (i < 8)
//	{
//		printf("tab_param[%i] = %s\n", i, tab_param[i]);
//		i++;
//	}
	param->map.map = tab_map;
	param->map.nb_lines = j;
//	i = 0;
//	while (i < 8)
//	{
//		manage_param(tab_param[i], param);
//		i++;
//	}
print_params(param);
	return (0);
}
