/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 23:17:52 by llescure          #+#    #+#             */
/*   Updated: 2020/12/05 20:41:55 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			*ft_memmove(void *dest, const void *src, size_t len)
{
	char						*tempdest;
	const char					*tempsrc;
	int							i;

	tempdest = dest;
	tempsrc = src;
	if (dest > src)
	{
		i = len - 1;
		while (i >= 0)
		{
			tempdest[i] = tempsrc[i];
			i--;
		}
	}
	else
		ft_memcpy(dest, src, len);
	return (dest);
}
