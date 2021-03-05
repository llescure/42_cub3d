/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 23:13:56 by slescure          #+#    #+#             */
/*   Updated: 2021/03/03 11:14:10 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		colour_params_colour(char *str, t_param *param)
{
	char	**par;
	int		i;

	i = 0;
	par = ft_split(str, ',');
	param->colour.red = ft_atoi_cub3d(par[0], 1);
	param->colour.green = ft_atoi_cub3d(par[1], 0);
	param->colour.blue = ft_atoi_cub3d(par[2], 0);
	if ((param->colour.red < 0 || param->colour.red > 255) ||
			(param->colour.green < 0 || param->colour.green > 255) ||
			(param->colour.blue < 0 || param->colour.blue > 255))
	{
		perror("ERROR : wrong format of colour in the map");
		exit(0);
	}
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
	param->ground_colour.red = ft_atoi_cub3d(par[0], 1);
	param->ground_colour.green = ft_atoi_cub3d(par[1], 0);
	param->ground_colour.blue = ft_atoi_cub3d(par[2], 0);
	if ((param->ground_colour.green < 0 || param->ground_colour.green > 255) ||
			(param->ground_colour.red < 0 || param->ground_colour.red > 255) ||
			(param->ground_colour.blue < 0 || param->ground_colour.blue > 255))
	{
		perror("ERROR : wrong format of ground colour in the map");
		exit(0);
	}
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
	printf("cooucou\n");
	param->resolution.axe_x = ft_atoi_cub3d(par[1], 0);
	param->resolution.axe_y = ft_atoi_cub3d(par[2], 0);
	printf("la\n");
	while (i < 3)
	{
		free(par[i]);
		i++;
	}
	printf("ici?\n");
	free(par);
	return (0);
}

char	*save_address_param(char *str)
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
	return (address);
}

int		perso_orientation_position(char *str, t_param *param, int position)
{
	char	result;
	int		nb_result;
	int		i;

	nb_result = 0;
	i = -1;
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
	{
		perror("ERROR : too many characters in the map");
		exit(0);
	}
	if (position != 0)
	{
		param->perso.position_x = position;
		param->perso.orientation = result;
	}
	return (nb_result);
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
		perror("ERROR : wrong number of arguments");
		exit(0);
	}
	free(map_params);
	return (0);
}
