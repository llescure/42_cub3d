#include "../include/cub3d.h"
#include "../include/struct_cub3d.h"

int		move_to_map(char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\n'
		|| (str[i + 1] != '1' && str[i + 1] != ' ' && str[i + 1] != '\0'))
		i++;
	while (str[i] == '\n')
		i++;
	return (i);
}

char	*only_map(char *str, t_param *param)
{
	int		i;
	int		j;
	char	*map;

	j = 0;
	i = move_to_map(str);
	if (!(map = malloc(sizeof(char) * calculate_nb_chains(str)
		* ft_biggest_line_len(str))))
		return (NULL);
	while (str[i] != '\0')
	{
		if (str[i] == '\n' && str[i + 1] != '1' && str[i + 1] != ' '
				&& str[i + 1] != '\0')
			print_error(param, "Error in the map");
		if (str[i] == ' ')
			map[j] = '1';
		else
			map[j] = str[i];
		i++;
		j++;
	}
	map[j] = '\0';
	param->map.map = map;
	param->map.nb_lines = calculate_nb_chains(map);
	return (map);
}

char	**creation_table_map(char **str, t_param *param)
{
	int		i;
	int		j;
	char	**map;

	map = malloc_tab(param);
	j = 0;
	while (j < param->map.nb_lines)
	{
		i = 0;
		while (str[j][i] == ' ')
			map[j][i++] = '5';
		i--;
		while (++i > -1 && str[j][i] != '\0')
		{
			if (str[j][i] == ' ')
				map[j][i] = '5';
			else
				map[j][i] = str[j][i];
		}
		while (i < param->map.max_length)
			map[j][i++] = '5';
		map[j++][i] = '\0';
	}
	free_str(str, param);
	return (map);
}

void	free_str(char **str, t_param *param)
{
	int i;

	i = 0;
	while (i < param->map.nb_lines)
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int		read_next_line(char **tab_map, char **tab_param, char **line, int fd, t_param *param)
{
	int i;
	int j;
	int ret;

	ret = 1;
	i = 0;
	j = 0;
	while ((ret = get_next_line(fd, line)) > 0)
	{
		if ((*line)[0] == 'C' || (*line)[0] == 'R' || (*line)[0] == 'S'
				|| (*line)[0] == 'F'
				|| (*line)[0] == 'E' || (*line)[0] == 'W' || (*line)[0] == 'N')
			tab_param[i++] = strdup(*line);
		if ((*line)[0] == ' ' || (*line)[0] == '1')
			tab_map[j++] = strdup(*line);
		free(*line);
	}
	if (i < 8)
		print_error(param, "Wrong number of parameters");
	free(*line);
	return (ret);
}

int		sorting_map(char *map_map, t_param *param)
{
	int		fd;
	int		ret;
	char	**tab_param;
	char	**tab_map;
	char	*line;

	ret = 1;
	fd = open(param->file, O_RDONLY);
	if (!(tab_param = malloc(sizeof(char*) * 8)))
		return (-1);
	if (!(tab_map = malloc(sizeof(char*) * calculate_nb_chains(map_map))))
		return (-1);
	ret = read_next_line(tab_map, tab_param, &line, fd, param);
	tab_map = creation_table_map(tab_map, param);
	param->map.tab_map = tab_map;
	check_all_para(param, tab_param);
	ret = 0;
	while (ret < 8)
	{
		free(tab_param[ret]);
		ret++;
	}
	free(tab_param);
	printf("PARAMETERS = [OK]\n");
	return (0);
}
