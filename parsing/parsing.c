#include "../include/cub3D.h"
#include "../include/struct_cub3D.h"

void		free_address_params(t_param *param)
{
	int i;

	if (param->sprite)
		free(param->sprite);
	if (param->north_texture)
		free(param->north_texture);
	if (param->south_texture)
		free(param->south_texture);
	if (param->east_texture)
		free(param->east_texture);
	if (param->west_texture)
		free(param->west_texture);
	if (param->map.map)
		free(param->map.map);
	i = 0;
	while (i < param->map.nb_lines)
	{
		free(param->map.tab_map[i]);
		i++;
	}
	free(param->map.tab_map);
}

t_param		initialize_structure(t_param *param, char *argv)
{
	param->map.tab_map = NULL;
	param->map.map = NULL;
	param->file = argv;
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

int			read_map(int fd, char *str, char *map, t_param *para)
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
	close(fd);
	only_params(map, para);
	str = only_map(map, para);
	check_void_line_map(str, para);
	para->map.max_length = ft_biggest_line_len(str);
	sorting_map(map, para);
	check_map(para->map.tab_map, para->map.nb_lines, para->map.max_length, para);
	free(map);
	return (0);
}

/*int			main(int argc, char **argv)
{
	char	*str;
	char	*map;
	int		fd;
	t_param	param;

	if (!(map = malloc(sizeof(char) * 2)))
		return (-1);
	map[0] = 0;
	if (!(str = malloc(sizeof(char) * 2)))
		return (-1);
	initialize_structure(&param, argv[1]);
	fd = open(argv[1], O_RDONLY);
	manage_errors(argc, argv, &param);
	read_map(fd, str, map, &param);
	print_params(&param);
	init(&param);
	free_address_params(&param);
	return (0);
}*/

t_param		initialize(int argc, char **argv)
{
	char	*str;
	char	*map;
	int		fd;
	t_param	param;

	map = malloc(sizeof(char) * 2);
	map[0] = 0;
	str = malloc(sizeof(char) * 2);
	initialize_structure(&param, argv[1]);
	fd = open(argv[1], O_RDONLY);
	manage_errors(argc, argv, &param);
	read_map(fd, str, map, &param);
	free(str);
	print_params(&param);
	return (param);
}
