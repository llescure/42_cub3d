/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_address.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 15:41:36 by slescure          #+#    #+#             */
/*   Updated: 2021/03/08 15:51:32 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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

int		check_address_parameters(char *str)
{
	char	*comp;

	comp = "./textures/";
	if (find_str_beginning(str, comp) == 0)
	{
		perror("ERROR\nWrong address");
		exit(0);
	}
	comp = ".xpm";
	if (find_str_end(str, comp) == 0)
	{
		perror("ERROR\nWrong address");
		exit(0);
	}
	return (0);
}
