/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parametres.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:37:45 by slescure          #+#    #+#             */
/*   Updated: 2021/02/09 19:34:32 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_atoi_cub3d(char *str, int i)
{
	int				signe;
	unsigned int	resultat;

	signe = 1;
	resultat = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\f'
			|| str[i] == '\r' || str[i] == ' ' || str[i] == '\v')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			signe = -signe;
		i++;
		if (str[i] == '+' || str[i] == '-')
			return (0);
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		resultat = (resultat * 10) + (str[i] - 48);
		i++;
	}
	return (resultat * signe);
}
int		colour_params_colour(char *str, t_param *param) // good mais faut structure de structure pour differencier C et F
{
	char **par;

	par = ft_split(str, ',');
	param->colour.red = ft_atoi_cub3d(par[0], 1);
	param->colour.green = ft_atoi_cub3d(par[1], 0);
	param->colour.blue = ft_atoi_cub3d(par[2], 0);
	if ((param->colour.red < 0 && param->colour.red > 255) ||
		(param->colour.green < 0 && param->colour.green > 255) ||
		(param->colour.blue < 0 && param->colour.blue > 255))
//	printf("red = %i\n", param->colour.red);
//	printf("green = %i\n", param->colour.green);
//	printf("blue = %i\n", param->colour.blue);
	free(par);
	return (0);
}

int		colour_params_ground(char *str, t_param *param) // good mais faut structure de structure pour differencier C et F
{
	char **par;

	par = ft_split(str, ',');
	param->ground_colour.red = ft_atoi_cub3d(par[0], 1);
	param->ground_colour.green = ft_atoi_cub3d(par[1], 0);
	param->ground_colour.blue = ft_atoi_cub3d(par[2], 0);
//	printf("red = %i\n", param->ground_colour.red);
//	printf("green = %i\n", param->ground_colour.green);
//	printf("blue = %i\n", param->ground_colour.blue);
	free(par);
	return (0);
}

int		resolution_param(char *str, t_param *param) //good
{
	char **par;

	par = ft_split(str, ' ');
	param->resolution.axe_x = ft_atoi_cub3d(par[1], 0);
	param->resolution.axe_y = ft_atoi_cub3d(par[2], 0);
//	printf("x = %i\n", param->resolution.axe_x);
//	printf("y = %i\n", param->resolution.axe_y);
	free(par);
	return (0);
}

char	*recuperation_adresse_param(char *str)
{
	int i;
	int j;
	char *address;

	i = 2;
	j = 0;
	if (!(address = malloc(sizeof(char) * ft_strlen(str) + 1)))
		return (NULL);
	while (str[i] == ' ')
		i++;
	while (str[i] != '\0')
	{
		address[j] = str[i];
		i++;
		j++;
	}
	address[i] = '\0';
	printf("%s\n", address);
	return (address);
}
