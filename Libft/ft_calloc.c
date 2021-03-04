/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/20 16:59:55 by slescure          #+#    #+#             */
/*   Updated: 2019/10/20 17:00:10 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	char	*str;
	long	i;
	long	s;

	i = 0;
	s = (long)(count * size);
	if (!(str = malloc(s * sizeof(char))))
		return (NULL);
	while (i < s)
	{
		str[i] = 0;
		i++;
	}
	return (str);
}
