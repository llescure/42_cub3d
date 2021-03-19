#include "../include/cub3D.h"
#include "../include/struct_cub3D.h"

int		colour_params_colour(char *str, t_param *param)
{
	char	**par;
	int		i;

	i = 0;
	par = ft_split(str, ',');
	param->colour.red = ft_atoi_cub3d(par[0], 1, param);
	param->colour.green = ft_atoi_cub3d(par[1], 0, param);
	param->colour.blue = ft_atoi_cub3d(par[2], 0, param);
	if ((param->colour.red < 0 || param->colour.red > 255) ||
			(param->colour.green < 0 || param->colour.green > 255) ||
			(param->colour.blue < 0 || param->colour.blue > 255))
		print_error(param, "Wrong format of colour in the map");
	while (i < 3)
	{
		free(par[i]);
		i++;
	}
	free(par);
	return (0);
}

int		colour_params_ground(char *str, t_param *param)
{
	int		i;
	char	**par;

	i = 0;
	par = ft_split(str, ',');
	param->ground_colour.red = ft_atoi_cub3d(par[0], 1, param);
	param->ground_colour.green = ft_atoi_cub3d(par[1], 0, param);
	param->ground_colour.blue = ft_atoi_cub3d(par[2], 0, param);
	if ((param->ground_colour.green < 0 || param->ground_colour.green > 255) ||
			(param->ground_colour.red < 0 || param->ground_colour.red > 255) ||
			(param->ground_colour.blue < 0 || param->ground_colour.blue > 255))
		print_error(param, "Wrong format of ground colour in the map");
	while (i < 3)
	{
		free(par[i]);
		i++;
	}
	free(par);
	return (0);
}

int		resolution_param(char *str, t_param *param)
{
	int		i;
	char	**par;

	i = 0;
	par = ft_split(str, ' ');
	while (ft_isdigit(str[i]) == 0)
		i++;
	while (ft_isdigit(str[i]) == 1)
		i++;
	if (!(ft_isdigit(str[i - 1]) == 1 && str[i] == ' '
		&& ft_isdigit(str[i + 1]) == 1 && par[3] == NULL))
		print_error(param, "Wrong writing of resolution");
	param->resolution.axe_x = ft_atoi_cub3d(par[1], 0, param);
	param->resolution.axe_y = ft_atoi_cub3d(par[2], 0, param);
	i = -1;
	while (++i < 3)
		free(par[i]);
	free(par);
	return (0);
}

char	*save_address_param(char *str, t_param *param)
{
	size_t	i;
	int		j;
	char	*address;

	i = 0;
	j = 0;
	while (str[i] != '.')
		i++;
	if (!(address = malloc(sizeof(char) * (ft_strlen(str) - i + 1))))
		return (NULL);
	while (str[i] != '\0')
	{
		address[j] = str[i];
		i++;
		j++;
	}
	address[j] = '\0';
	check_address_parameters(address, param);
	return (address);
}

int		p_orientation_position(char *str, t_param *param, int position, int i)
{
	char	result;
	int		nb_result;

	nb_result = 0;
	while (str[++i] != '\0')
	{
		if (str[i] == 'N' || str[i] == 'S' || str[i] == 'E' || str[i] == 'W')
		{
			result = str[i];
			position = i;
			nb_result++;
		}
	}
	if (nb_result > 1)
		print_error(param, "Too many characters in the map");
	if (position != 0)
	{
		param->perso.position_x = position;
		param->perso.orientation = result;
	}
	return (nb_result);
}
