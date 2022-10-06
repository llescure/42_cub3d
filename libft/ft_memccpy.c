/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 23:15:52 by llescure          #+#    #+#             */
/*   Updated: 2020/11/01 20:49:29 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	unsigned int		i;
	unsigned char		*tempdest;
	unsigned const char	*tempsrc;

	i = 0;
	tempdest = dest;
	tempsrc = src;
	while (i < n)
	{
		tempdest[i] = tempsrc[i];
		if (tempsrc[i] == (unsigned char)c)
			return (&tempdest[i + 1]);
		i++;
	}
	return (NULL);
}
