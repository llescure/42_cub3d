#include "../include/cub3D.h"
#include "../include/struct_cub3D.h"

int		check_void_line_map(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n' && str[i + 1] == '\n')
		{
			perror("ERROR\nVoid line in the map");
			exit(0);
		}
		i++;
	}
	return (0);
}

int		calculate_nb_chains(char *str)
{
	int	result;
	int	i;

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

int		only_params(char *str)
{
	int		i;
	char	*map_params;

	i = 0;
	if (!(map_params = malloc(sizeof(char) * ft_strlen(str))))
		return (-1);
	while (str[i] != '\0')
	{
		if (str[i] == '\n' && (str[i + 1] == '1' || str[i + 1] == ' '))
		{
			map_params[i] = '\0';
			break ;
		}
		else
			map_params[i] = str[i];
		i++;
	}
	i = calculate_nb_chains(map_params);
	if (i != 8)
	{
		perror("ERROR\nWrong number of arguments");
		exit(0);
	}
	free(map_params);
	return (0);
}
