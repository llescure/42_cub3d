/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 23:32:51 by llescure          #+#    #+#             */
/*   Updated: 2020/11/02 19:15:12 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t			ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	unsigned int				i;
	unsigned int				j;
	unsigned int				size;

	size = ft_strlen(dst);
	i = size;
	j = 0;
	while (i + 1 < dstsize && j < (ft_strlen(src)))
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	if (!((dstsize == 0) || (size > dstsize)))
		dst[i] = '\0';
	if (dstsize < size)
		return (dstsize + ft_strlen((char *)src));
	else
		return (size + ft_strlen((char *)src));
}
