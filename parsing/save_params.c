/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 20:23:52 by llescure          #+#    #+#             */
/*   Updated: 2021/05/03 20:23:54 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/struct_cub3d.h"

void	colour_params(char *str, t_param *param, t_colour *up_down,
		char **texture)
{
	char	**colour;

	if (ft_strchr(str, ',') == NULL)
	{
		*texture = save_address_param(str, param);
		return ;
	}
	if (ft_number_occurence(str, ',') != 2)
		print_error(param, "Wrong format of colour in the map");
	colour = ft_split(str, ',');
	up_down->red = ft_atoi_cub3d(colour[0], 1, param);
	up_down->green = ft_atoi_cub3d(colour[1], 0, param);
	up_down->blue = ft_atoi_cub3d(colour[2], 0, param);
	if ((up_down->red < 0 || up_down->red > 255) ||
		(up_down->green < 0 || up_down->green > 255)
		|| (up_down->blue < 0 || up_down->blue > 255))
		print_error(param, "Wrong format of colour in the map");
	free_param_colour(colour);
	return ;
}

void	free_param_colour(char **colour)
{
	int i;

	i = 0;
	while (i < 3)
	{
		free(colour[i]);
		i++;
	}
	free(colour);
}

void	resolution_param(char *str, t_param *param)
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
}

char	*save_address_param(char *str, t_param *param)
{
	size_t	i;
	int		j;
	char	*address;

	i = 2;
	j = 0;
	while (str[i] == ' ' && str[i] != '\0')
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
