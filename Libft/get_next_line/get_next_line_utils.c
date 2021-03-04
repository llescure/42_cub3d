/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/16 15:49:38 by slescure          #+#    #+#             */
/*   Updated: 2021/03/04 16:04:39 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char		*ft_strchr(char *str, int c)
{
	unsigned int	i;

	i = 0;
	if (c == '\0' && str[0] == '\0')
		return (str);
	while (i <= ft_strlen(str))
	{
		if (c == str[i])
			return ((char *)&str[i]);
		i++;
	}
	return (NULL);
}

char		*get_rest(char *str)
{
	char	*rest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	rest = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (rest == NULL)
		return (NULL);
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\0')
		return (rest);
	i++;
	while (str[i] != '\0')
	{
		rest[j] = str[i];
		i++;
		j++;
	}
	rest[j] = '\0';
	return (rest);
}

char		*get_line(char *str)
{
	int		i;
	int		n;
	char	*rslt;

	i = 0;
	n = 0;
	while (str[n] != '\n' && str[n] != '\0')
		n++;
	rslt = malloc(sizeof(char) * n + 1);
	if (rslt == NULL)
		return (NULL);
	while (i < n)
	{
		rslt[i] = str[i];
		i++;
	}
	rslt[i] = '\0';
	return (rslt);
}
