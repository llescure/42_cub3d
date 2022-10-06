/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/11 16:09:43 by llescure          #+#    #+#             */
/*   Updated: 2021/05/03 15:16:40 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_trim(char *str, int c)
{
	char					*new_str;
	unsigned int			i;
	unsigned int			size;

	size = 0;
	while (str[size] != '\0' && str[size] != c)
		size++;
	if (!(new_str = malloc(sizeof(char) * size + 1)))
		return (NULL);
	i = 0;
	while (i < size)
	{
		new_str[i] = str[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char		*get_temp(char *str, int c)
{
	unsigned int	i;
	unsigned int	j;
	char			*temp;

	i = 0;
	j = 0;
	if (!(temp = malloc(sizeof(char) * ft_strlen(str) + 1)))
		return (NULL);
	while (str[i] != '\0' && str[i] != c)
		i++;
	if (str[i] == '\0')
		return (temp);
	i++;
	while (str[i] != '\0')
	{
		temp[j] = str[i];
		j++;
		i++;
	}
	temp[j] = '\0';
	return (temp);
}
