/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_address.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 20:22:49 by llescure          #+#    #+#             */
/*   Updated: 2021/05/03 20:22:51 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/struct_cub3d.h"

int		find_str_beginning(char *s1, char *s2)
{
	int		i;

	i = 0;
	while (s2[i] != '\0')
	{
		if (s1[i] != s2[i])
			return (0);
		i++;
	}
	return (1);
}

int		find_str_end(char *s1, char *s2)
{
	int		i;
	int		j;

	i = ft_strlen(s1);
	j = ft_strlen(s2);
	while (j >= 0 && i >= 0)
	{
		if (s1[i] != s2[j])
			return (0);
		i--;
		j--;
	}
	return (1);
}

void	check_address_parameters(char *str, t_param *param)
{
	char	*comp;

	comp = "./textures/";
	if (find_str_beginning(str, comp) == 0)
		print_error(param, "Wrong address");
	comp = ".xpm";
	if (find_str_end(str, comp) == 0)
		print_error(param, "Wrong address");
}
