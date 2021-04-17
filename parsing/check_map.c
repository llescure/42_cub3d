#include "../include/cub3d.h"
#include "../include/struct_cub3d.h"

int		check_end_walls(char *str, int length, t_param *param)
{
	int i;

	i = 0;
	length = length - 2;
	while (str[i] == '5')
		i++;
	if (str[i] != '1')
		print_error(param, "Wrong format of the map : no walls at the end");
	while (str[length] == '5')
		length--;
	if (str[length] != '1')
		print_error(param, "Wrong format of the map : no walls at the end");
	return (0);
}

int		check_symbols(char *str, t_param *param)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != 'E'
				&& str[i] != 'S' && str[i] != 'W' && str[i] != 'N'
				&& str[i] != '5' && str[i] != ' ' && str[i] != '3')
			print_error(param, "Wrong symbol in the map");
		i++;
	}
	return (0);
}

char	*check_space_in_map(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '5')
			str[i] = '1';
		i++;
	}
	return (str);
}

int		check_holes_walls(char **map, int nb_lines, int length, t_param *param)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < nb_lines)
	{
		while (j < length)
		{
			if ((map[i][j] == '0') && (map[i + 1][j] == '5'))
				print_error(param, "Wrong format of the map : holes in map");
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

int		check_first_last_string_map(char *str, t_param *param)
{
	int i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] != '1' && str[i] != '5' && str[1] == '\0' && str[2] == '\0')
			print_error(param, "Wrong format of the map : void");
		if (str[i] == '1' && str[i + 1] == '5' && str[i + 2] == '1')
			print_error(param, "Wrong format of the map : void");
	}
	return (0);
}
