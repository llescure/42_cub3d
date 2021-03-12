#include "parsing.h"

int		check_end_walls(char *str, int length)
{
	int result;
	int i;

	result = 0;
	i = 0;
	length = length - 2;
	while (str[i] == '5')
		i++;
	if (str[i] != '1')
	{
		perror("ERROR\nWrong format of the map : no walls at the end");
		exit(0);
	}
	while (str[length] == '5')
		length--;
	if (str[length] != '1')
	{
		perror("ERROR\nWrong format of the map : no walls at the end");
		exit(0);
	}
	return (0);
}

int		check_symbols(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != 'E'
				&& str[i] != 'S' && str[i] != 'W' && str[i] != 'N'
				&& str[i] != '5' && str[i] != ' ')
		{
			perror("ERROR\nWrong symbol in the map");
			exit(0);
		}
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

int		check_holes_walls(char **map, int nb_lines, int length)
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
			{
				perror("ERROR\nWrong format of the map : holes in the map");
				exit(0);
			}
			j++;
		}
		j = 0;
		i++;
	}
	return (0);
}

int		check_first_last_string_map(char *str)
{
	int i;

	i = -1;
	while (str[++i] != '\0')
	{
		if (str[i] != '1' && str[i] != '5' && str[1] == '\0' && str[2] == '\0')
		{
			perror("ERROR\nWrong format of the map : void");
			exit(0);
		}
		if (str[i] == '1' && str[i + 1] == '5' && str[i + 2] == '1')
		{
			perror("ERROR\nWrong format of the map : void");
			exit(0);
		}
	}
	return (0);
}
