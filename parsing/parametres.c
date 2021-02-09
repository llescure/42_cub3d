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
int		colour_params(char *str) // good mais faut structure de structure pour differencier C et F
{
	t_colour colour;
	char **par;

	par = ft_split(str, ',');
	colour.red = ft_atoi_cub3d(par[0], 1);
	colour.green = ft_atoi_cub3d(par[1], 0);
	colour.blue = ft_atoi_cub3d(par[2], 0);
	printf("red = %i\n", colour.red);
	printf("green = %i\n", colour.green);
	printf("blue = %i\n", colour.blue);
	return (0);
}

int		resolution_param(char *str) //good
{
	t_resolution resolution;
	char **par;

	par = ft_split(str, ' ');
	resolution.axe_x = ft_atoi_cub3d(par[1], 0);
	resolution.axe_y = ft_atoi_cub3d(par[2], 0);
	printf ("x = %i\n", resolution.axe_x);
	printf ("y = %i\n", resolution.axe_y);
	return (0);
}

char	*recuperation_adresse_param(char *str)
{
	int i;
	int j;
	char *address;

	i = 2;
	j = 0;
	if (!(address = malloc(sizeof(char) * ft_strlen(str))))
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
