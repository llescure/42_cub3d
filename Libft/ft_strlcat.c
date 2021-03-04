/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 13:43:15 by slescure          #+#    #+#             */
/*   Updated: 2019/10/28 16:37:46 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t i;
	size_t j;
	size_t x;

	j = 0;
	i = 0;
	while (dest[i] && i < size)
		i++;
	x = ft_strlen(src);
	if (i == size)
		return (size + ft_strlen(src));
	if (size == 0)
		return (x);
	if (size < i)
		x += size;
	else
		x += i;
	while (src[j] != '\0' && i < size - 1 && dest != src)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (x);
}
