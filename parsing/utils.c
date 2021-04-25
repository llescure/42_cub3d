#include "../include/cub3d.h"
#include "../include/struct_cub3d.h"

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
	if (str == NULL)
		print_error(param, "Wrong writing of color");
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\f' || str[i] == '\v'
			|| str[i] == '\r' || str[i] == ' ')
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

int		conversion_rgb_to_hexa(t_colour colour)
{
	int red;
	int green;
	int blue;

	red = colour.red;
	green = colour.green;
	blue = colour.blue;
	return ((red << 16) | (green << 8) | blue);
}

int ft_number_sprites(char *str, t_param *param)
{
	int i;
	int result;
	int x;
	int y;

	i = 0;
	result = 0;
	x = 0;
	y = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '2' || str[i] == '3')
			result++;
		if (str[i] == '2')
			x++;
		if (str[i] == '3')
			y++;
		i++;
	}
	param->nb_sprite_1 = x;
	param->nb_sprite_2 = y;
	return (result);
}
