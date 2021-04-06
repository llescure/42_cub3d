#include "../include/cub3D.h"
#include "../include/struct_cub3D.h"

int		manage_perso(char **map, t_param *param)
{
	int i;
	int j;
	int result;

	i = 0;
	j = 0;
	result = 0;
	while (i < param->map.nb_lines)
	{
		if (p_orientation_position(map[i], param, 0, -1) == 1)
		{
			param->perso.position_y = i;
			result++;
			while (map[i][j] != '\0')
			{
				if (ft_isalpha(map[i][j]) == 1)
					param->map.tab_map[i][j] = '0';
				j++;
			}
		}
		i++;
	}
	if (result != 1)
		print_error(param, "Wrong number of characters in the map");
	i = 0;
	printf("CHARACTER : [OK]\n");
	return (0);
}

int		manage_param(char *str, t_param *param)
{
	if (str[0] == 'C' && str[1] == ' ')
		colour_params_ceiling(str, param);
	if (str[0] == 'R' && str[1] == ' ')
		resolution_param(str, param);
	if (str[0] == 'S' && str[1] == ' ')
		param->sprite = save_address_param(str, param);
	if (str[0] == 'F')
		colour_params_floor(str, param);
	if (str[0] == 'N' && str[1] == 'O' && str[2] == ' ')
		param->north_texture = save_address_param(str, param);
	if (str[0] == 'S' && str[1] == 'O' && str[2] == ' ')
		param->south_texture = save_address_param(str, param);
	if (str[0] == 'E' && str[1] == 'A' && str[2] == ' ')
		param->east_texture = save_address_param(str, param);
	if (str[0] == 'W' && str[1] == 'E' && str[2] == ' ')
		param->west_texture = save_address_param(str, param);
	return (0);
}

int		check_all_para(t_param *param, char **tab_param)
{
	int i;

	i = -1;
	while (++i < 8)
		manage_param(tab_param[i], param);
	if (param->ceiling_colour.red == -10 || param->ceiling_colour.green == -10
			|| param->ceiling_colour.blue == -10 ||
			param->floor_colour.green == -10 ||
			param->floor_colour.blue == -10 || param->floor_colour.red == -10)
		print_error(param, "Missing colour");
	if (param->resolution.axe_x == -10 || param->resolution.axe_y == -10)
		print_error(param, "Missing resolution");
	if (param->sprite == NULL || param->north_texture == NULL ||
			param->south_texture == NULL || param->east_texture == NULL ||
			param->west_texture == NULL)
		print_error(param, "Missing texture");
	return (0);
}

int		check_map(char **map, int nb_lines, int max_length, t_param *param)
{
	int i;

	i = -1;
	while (++i < nb_lines)
	{
		check_end_walls(map[i], max_length, param);
		check_symbols(map[i], param);
	}
	if (param->map.max_length == 2 || param->map.max_length == 3)
	print_error(param, "Wrong format of map");

	check_first_last_string_map(map[0], param);
	check_first_last_string_map(map[nb_lines - 1], param);
	check_holes_walls(map, nb_lines, max_length, param);
	i = -1;
	while (++i < nb_lines)
		map[i] = check_space_in_map(map[i]);
	manage_perso(map, param);
	printf("MAP : [OK]\n");
	return (0);
}
