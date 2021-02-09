/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 15:38:30 by slescure          #+#    #+#             */
/*   Updated: 2021/02/09 15:58:28 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char		*ft_strjoin(char *s1, char *s2)
{
	size_t		i;
	size_t		j;
	char		*dest;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	dest = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (dest == NULL)
		return (NULL);
	dest[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	i = -1;
	while (s1[++i] != '\0')
		dest[i] = s1[i];
	j = 0;
	while (s2[j] != '\0')
		dest[i++] = s2[j++];
	dest[i] = '\0';
	return (dest);
}
