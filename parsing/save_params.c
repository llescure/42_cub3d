#include "../include/cub3d.h"
#include "../include/struct_cub3d.h"

int		colour_params_ceiling(char *str, t_param *param)
{
	char	**par;
	int		i;

	i = 0;
	if (ft_strchr(str, ',') == NULL)
	{
		param->ceiling_texture = save_address_param(str, param);
		return (0);
	}
	par = ft_split(str, ',');
	param->ceiling_colour.red = ft_atoi_cub3d(par[0], 1, param);
	param->ceiling_colour.green = ft_atoi_cub3d(par[1], 0, param);
	param->ceiling_colour.blue = ft_atoi_cub3d(par[2], 0, param);
	if ((param->ceiling_colour.red < 0 || param->ceiling_colour.red > 255) ||
		(param->ceiling_colour.green < 0 || param->ceiling_colour.green >
		255) || (param->ceiling_colour.blue < 0 ||
		param->ceiling_colour.blue > 255))
		print_error(param, "Wrong format of colour in the map");
	while (i < 3)
	{
		free(par[i]);
		i++;
	}
	free(par);
	return (0);
}

int		colour_params_floor(char *str, t_param *param)
{
	int		i;
	char	**par;

	i = 0;
	if (ft_strchr(str, ',') == NULL)
	{
		param->floor_texture = save_address_param(str, param);
		return (0);
	}
	par = ft_split(str, ',');
	param->floor_colour.red = ft_atoi_cub3d(par[0], 1, param);
	param->floor_colour.green = ft_atoi_cub3d(par[1], 0, param);
	param->floor_colour.blue = ft_atoi_cub3d(par[2], 0, param);
	if ((param->floor_colour.green < 0 || param->floor_colour.green > 255) ||
			(param->floor_colour.red < 0 || param->floor_colour.red > 255) ||
			(param->floor_colour.blue < 0 || param->floor_colour.blue > 255))
		print_error(param, "Wrong format of floor colour in the map");
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
	if (param->resolution.axe_x < 100 || param->resolution.axe_y < 100)
		print_error(param, "Resolution too low");
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
	while (str[i] != '.' && str[i] != '\0')
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
	result = '0';
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
