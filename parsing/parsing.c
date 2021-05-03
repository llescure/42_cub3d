/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 20:23:32 by llescure          #+#    #+#             */
/*   Updated: 2021/05/03 20:23:34 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/struct_cub3d.h"

void		free_address_params(t_param *param)
{
	int i;

	if (param->sprite_1)
		free(param->sprite_1);
	if (param->sprite_2)
		free(param->sprite_2);
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
	i = -1;
	if (param->map.tab_map)
	{
		while (++i < param->map.nb_lines)
			free(param->map.tab_map[i]);
		free(param->map.tab_map);
	}
}

t_param		initialize_structure(t_param *param, char *argv)
{
	param->map.tab_map = NULL;
	param->map.map = NULL;
	param->file = argv;
	param->ceiling_colour.red = -10;
	param->ceiling_colour.blue = -10;
	param->ceiling_colour.green = -10;
	param->floor_colour.red = -10;
	param->floor_colour.blue = -10;
	param->floor_colour.green = -10;
	param->resolution.axe_x = -10;
	param->resolution.axe_y = -10;
	param->sprite_1 = NULL;
	param->sprite_2 = NULL;
	param->north_texture = NULL;
	param->south_texture = NULL;
	param->west_texture = NULL;
	param->east_texture = NULL;
	param->ceiling_texture = NULL;
	param->floor_texture = NULL;
	param->bonus = '0';
	param->perso.orientation = 0;
	param->perso.position_x = -10;
	param->perso.position_y = -10;
	return (*param);
}

void		read_map(int fd, char *str, char *map, t_param *para)
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
	store_params(map, para);
	str = store_map(map, para);
	para->nb_sprites = ft_number_sprites(str) + 1;
	check_void_line_map(str, para);
	para->map.max_length = ft_biggest_line_len(str);
	if (para->map.max_length > 300)
		print_error(para, "Line too big");
	sorting_map(map, para);
	check_map(para->map.tab_map, para->map.nb_lines,
			para->map.max_length, para);
	free(map);
}

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
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		print_error(&param, "Couldn't open file.cub");
	manage_errors(argc, argv, &param);
	read_map(fd, str, map, &param);
	free(str);
	param.perso.position_x += 0.5;
	param.perso.position_y += 0.5;
	return (param);
}

void		free_str(char **str, t_param *param)
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
