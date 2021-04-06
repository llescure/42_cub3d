#include "../include/cub3D.h"
#include "../include/struct_cub3D.h"

char	**malloc_tab(t_param *param)
{
	int		i;
	char	**tab;

	i = 0;
	if (!(tab = malloc(sizeof(char*) * param->map.nb_lines)))
		return (NULL);
	while (i < param->map.nb_lines)
	{
		if (!(tab[i] = malloc(sizeof(char) * param->map.max_length + 1)))
			return (NULL);
		i++;
	}
	return (tab);
}

int		ft_atoi_cub3d(char *str, int i, t_param *param)
{
	int				sign;
	unsigned int	result;

	sign = 1;
	result = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\f'
			|| str[i] == '\r' || str[i] == ' ' || str[i] == '\v')
		i++;
	if (str[i] == '+' || str[i] == '-')
		print_error(param, "Wrong writing of parameters");
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - 48);
		i++;
	}
	if (str[i] == ' ' && ft_isdigit(str[i + 1]) == 1)
		print_error(param, "Wrong writing of parameters");
	if (str == NULL || ft_isalpha(str[i]) == 1 || result > 9999)
		print_error(param, "Wrong writing of parameters");
	return (result * sign);
}

int		ft_is_string(char *s1, char *s2)
{
	int		i;
	size_t	n;

	i = 0;
	n = 0;
	while (s1[i] != '\0')
	{
		if (s1[i] == s2[i])
			n++;
		i++;
	}
	if (n == ft_strlen(s1))
		return (1);
	return (0);
}

/*void	print_params(t_param *param)
{
	int i;

	printf("fichier = %s\n", param->file);
	printf("map = %s\n", param->map.map);
	printf("nb_lines = %i\n", param->map.nb_lines);
	printf("ceiling_color_red : %i\n", param->ceiling_colour.red);
	printf("ceiling_color_green : %i\n", param->ceiling_colour.green);
	printf("ceiling_color_blue : %i\n", param->ceiling_colour.blue);
	printf("color_ground_red : %i\n", param->ground_colour.red);
	printf("color_ground_green : %i\n", param->ground_colour.green);
	printf("color_ground_blue : %i\n", param->ground_colour.blue);
	printf("resolution_x : %i\n", param->resolution.axe_x);
	printf("resolution_y : %i\n", param->resolution.axe_y);
	printf("addrese sprite : %s\n", param->sprite);
	printf("addrese north : %s\n", param->north_texture);
	printf("addrese south : %s\n", param->south_texture);
	printf("addrese east : %s\n", param->east_texture);
	printf("addrese west : %s\n", param->west_texture);
	printf("position perso x = %f\n", param->perso.position_x);
	printf("position perso y = %f\n", param->perso.position_y);
	printf("orientation perso = %c\n", param->perso.orientation);
	i = 0;
	while (i < param->map.nb_lines)
	{
		printf("map[%i] = %s\n", i, param->map.tab_map[i]);
		i++;
	}
}*/

int		conversion_RGB_to_hexa(t_colour colour)
{
	int red;
	int green;
	int blue;

	red = colour.red;
	green = colour.green;
	blue = colour.blue;
	return ((red<<16) | (green<<8) | blue);
}
