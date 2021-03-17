#include "../src/cub3D.h"
#include "../src/struct_cub3D.h"

int		manage_perso(char **map, t_param *param)
{
	int i;
	int result;

	i = 0;
	result = 0;
	while (i < param->map.nb_lines)
	{
		if (p_orientation_position(map[i], param, 0, -1) == 1)
		{
			param->perso.position_y = i;
			result++;
		}
		i++;
	}
	if (result != 1)
	{
		perror("ERROR\nwrong number of characters on the map");
		exit(0);
	}
	printf("CHARACTER : [OK]\n");
	return (0);
}

int		manage_param(char *str, t_param *param)
{
	if (str[0] == 'C' && str[1] == ' ')
		colour_params_colour(str, param);
	if (str[0] == 'R' && str[1] == ' ')
		resolution_param(str, param);
	if (str[0] == 'S' && str[1] == ' ')
		param->sprite = save_address_param(str);
	if (str[0] == 'F')
		colour_params_ground(str, param);
	if (str[0] == 'N' && str[1] == 'O' && str[2] == ' ')
		param->north_texture = save_address_param(str);
	if (str[0] == 'S' && str[1] == 'O' && str[2] == ' ')
		param->south_texture = save_address_param(str);
	if (str[0] == 'E' && str[1] == 'A' && str[2] == ' ')
		param->east_texture = save_address_param(str);
	if (str[0] == 'W' && str[1] == 'E' && str[2] == ' ')
		param->west_texture = save_address_param(str);
	return (0);
}

int		check_all_para(t_param *param, char **tab_param)
{
	int i;

	i = -1;
	while (++i < 8)
		manage_param(tab_param[i], param);
	if (param->colour.red == -10 || param->colour.green == -10 ||
			param->colour.blue == -10 || param->ground_colour.green == -10 ||
			param->ground_colour.blue == -10 || param->ground_colour.red == -10)
	{
		perror("ERROR\nMissing colour");
		exit(0);
	}
	if (param->resolution.axe_x == -10 || param->resolution.axe_y == -10)
	{
		perror("ERROR\nMissing resolution");
		exit(0);
	}
	if (param->sprite == NULL || param->north_texture == NULL ||
			param->south_texture == NULL || param->east_texture == NULL ||
			param->west_texture == NULL)
	{
		perror("ERROR\nMissing texture or sprite");
		exit(0);
	}
	return (0);
}

int		check_map(char **map, int nb_lines, int max_length, t_param *param)
{
	int i;

	i = -1;
	while (++i < nb_lines)
	{
		check_end_walls(map[i], max_length);
		check_symbols(map[i]);
	}
	if (param->map.max_length == 2 || param->map.max_length == 3)
	{
		perror("ERROR\nWrong format of map");
		exit(0);
	}
	check_first_last_string_map(map[0]);
	check_first_last_string_map(map[nb_lines - 1]);
	check_holes_walls(map, nb_lines, max_length);
	i = -1;
	while (++i < nb_lines)
		map[i] = check_space_in_map(map[i]);
	manage_perso(map, param);
	printf("MAP : [OK]\n");
	return (0);
}
