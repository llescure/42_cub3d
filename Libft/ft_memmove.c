/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 14:10:45 by slescure          #+#    #+#             */
/*   Updated: 2019/10/20 17:30:46 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*src1;
	char	*dst1;
	size_t	x;

	src1 = (char *)src;
	dst1 = (char *)dst;
	if (src == dst)
		return (dst);
	if (src < dst)
	{
		x = len;
		while (x-- > 0)
			dst1[x] = src1[x];
	}
	else
	{
		x = 0;
		while (x < len)
		{
			dst1[x] = src1[x];
			x++;
		}
	}
	return (dst);
}
