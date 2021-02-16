/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_params.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 23:13:56 by slescure          #+#    #+#             */
/*   Updated: 2021/02/16 23:19:08 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		colour_params_colour(char *str, t_param *param) // good mais faut structure de structure pour differencier C et F
{
	char **par;
	int i;

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
		exit (0);
	}
//	printf("red = %i\n", param->colour.red);
//	printf("green = %i\n", param->colour.green);
//	printf("blue = %i\n", param->colour.blue);
	while (i < 3)
	{
		free(par[i]);
		i++;
	}
	free(par);
	return (0);
}

int		colour_params_ground(char *str, t_param *param) // good mais faut structure de structure pour differencier C et F
{
	int i;
	char **par;

	i = 0;
	par = ft_split(str, ',');
	param->ground_colour.red = ft_atoi_cub3d(par[0], 1);
	param->ground_colour.green = ft_atoi_cub3d(par[1], 0);
	param->ground_colour.blue = ft_atoi_cub3d(par[2], 0);
	if ((param->ground_colour.red < 0 || param->ground_colour.red > 255) ||
		(param->ground_colour.green < 0 || param->ground_colour.green > 255) ||
		(param->ground_colour.blue < 0 || param->ground_colour.blue > 255))
	{
		perror("ERROR : wrong format of ground colour in the map");
		exit (0);
	}
//	printf("red = %i\n", param->ground_colour.red);
//	printf("green = %i\n", param->ground_colour.green);
//	printf("blue = %i\n", param->ground_colour.blue);
	while (i < 3)
	{
		free(par[i]);
		i++;
	}
	free(par);
	return (0);
}

int		resolution_param(char *str, t_param *param) //good
{
	int i;
	char **par;

	i = 0;
	par = ft_split(str, ' ');
	param->resolution.axe_x = ft_atoi_cub3d(par[1], 0);
	param->resolution.axe_y = ft_atoi_cub3d(par[2], 0);
//	printf("x = %i\n", param->resolution.axe_x);
//	printf("y = %i\n", param->resolution.axe_y);
	while (i < 3)
	{
		free(par[i]);
		i++;
	}
	free(par);
	return (0);
}

char	*save_address_param(char *str)
{
	size_t 	i;
	int 	j;
	char 	*address;

	i = 0;
	j = 0;
	while (str[i] != '.')
		i++;
	if (!(address = malloc(sizeof(char) * (ft_strlen(str) - i))))
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

int     perso_orientation_position(char *str, t_param *param)
{
    char    result;
    int     nb_result;
    int     position;
    int		i;

    nb_result = 0;
	position = 0;
	i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == 'N' || str[i] == 'S' || str[i] == 'E' || str[i] == 'W')
        {
            result = str[i];
            position = i;
            nb_result++;
        }
        i++;
    }
    if (nb_result > 1)
    {
        perror("ERROR : too many characters in the map");
        exit (0);
    }
	if (position != 0)
	{
		param->perso.position_x = position;
		param->perso.orientation = result;
	}
    return (nb_result);
}
