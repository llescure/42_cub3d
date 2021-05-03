/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 20:23:06 by llescure          #+#    #+#             */
/*   Updated: 2021/05/03 20:24:54 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/struct_cub3d.h"

void	check_void_line_map(char *str, t_param *param)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n' && str[i + 1] == '\n')
			print_error(param, "Void line in the map");
		i++;
	}
}

int		calculate_nb_chains(char *str)
{
	int	result;
	int	i;

	i = 0;
	result = 0;
	if (str[0] == '\0')
		return (0);
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

void	store_params(char *str, t_param *param)
{
	int		i;
	char	*map_params;

	i = -1;
	if (!(map_params = malloc(sizeof(char) * ft_strlen(str) + 1)))
		print_error(param, "Couldn't allocate memory");
	while (str[++i] != '\0')
	{
		if (str[i] == '\n' && (str[i + 1] == '1' || str[i + 1] == ' '))
		{
			map_params[i] = '\0';
			break ;
		}
		else
			map_params[i] = str[i];
	}
	map_params[i] = '\0';
	i = calculate_nb_chains(map_params);
	param->nb_lines_params = i;
	free(map_params);
	if (i == 9 || i == 8)
		return ;
	else
		print_error(param, "Wrong number of arguments");
	return ;
}
