/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 15:11:39 by slescure          #+#    #+#             */
/*   Updated: 2021/03/03 11:24:26 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	**malloc_tab(t_param *param, char **tab)
{
	int	i;

	i = -1;
	if (!(tab = malloc(sizeof(char*) * param->map.nb_lines)))
		return (NULL);
	while (++i < param->map.nb_lines)
	{
		if (!(tab[i] = malloc(sizeof(char) * param->map.max_length)))
			return (NULL);
	}
	return (tab);
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

int		ft_atoi_cub3d(char *str, int i)
{
	int				sign;
	unsigned int	result;

	sign = 1;
	result = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\f'
			|| str[i] == '\r' || str[i] == ' ' || str[i] == '\v')
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
		if (str[i] == '+' || str[i] == '-')
			return (0);
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - 48);
		i++;
	}
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

void	print_params(t_param *param)
{
	int i;

	printf("fichier = %s\n", param->file);
	printf("map = %s\n", param->map.map[8]);
	printf("nb_lines = %i\n", param->map.nb_lines);
	printf("color_red : %i\n", param->colour.red);
	printf("color_green : %i\n", param->colour.green);
	printf("color_blue : %i\n", param->colour.blue);
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
	printf("position perso x = %i\n", param->perso.position_x);
	printf("position perso y = %i\n", param->perso.position_y);
	printf("orientation perso = %c\n", param->perso.orientation);
	i = 0;
	while (i < param->map.nb_lines)
	{
		free(param->map.map[i]);
		i++;
	}
}
