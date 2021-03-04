/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 14:10:26 by slescure          #+#    #+#             */
/*   Updated: 2019/10/20 17:26:14 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned int	i;
	char			*str;
	char			*str2;

	if (dest == src)
		return (dest);
	str = (char *)src;
	str2 = (char *)dest;
	i = 0;
	while (i < n)
	{
		str2[i] = str[i];
		i++;
	}
	return (dest);
}
