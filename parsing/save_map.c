/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 23:25:30 by slescure          #+#    #+#             */
/*   Updated: 2021/02/17 00:01:51 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

char	**creation_table_map(char **str, t_param *param)
{
	int i;
	int j;
	char **map;

    map = NULL;
    map = malloc_tab(param, map);
	j = 0;
	while (j < param->map.nb_lines)
	{
		i = 0;
		while (str[j][i] == ' ')
			map[j][i++] = '5';
		while (str[j][i] != '\0')
		{
			map[j][i] = str[j][i];
			i++;
		}
		while (i < param->map.max_length - 1)
			map[j][i++] = '5';
		map[j++][i] = '\0';
//		printf("nv_map[%i] = %s\n", j, map[j]);
	}
	i = -1;
	while (++i < param->map.nb_lines)
		free(str[i]);
	free (str);
	return (map);
}

int		sorting_map(char *map_map, t_param *param)
{
	int i;
	int j;
	int fd;
	int ret;
	char **tab_param;
	char **tab_map;
	char *line;

	i = 0;
	j = 0;
	ret =  1;
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
	param->map.nb_lines = j;
//	while (j < param->map.nb_lines)
//	{
//		printf("map[%i] = %s\n", j, tab_map[j]);
//		j++;
//	}
	tab_map = creation_table_map(tab_map, param); // remplacer par des '5' dans espace
	param->map.map = tab_map;
//	i = 0;
//	j = 0;
//	while (i < 8)
//	{
//		printf("tab_param[%i] = %s\n", i, tab_param[i]);
//		i++;
//	}
	check_all_para(param, tab_param);
	return (0);
}
