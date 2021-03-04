/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 16:10:48 by slescure          #+#    #+#             */
/*   Updated: 2019/10/14 17:32:27 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *chaine, int car)
{
	char *str;

	str = (char *)chaine;
	while (*str != car)
	{
		if (*str == '\0')
			return (NULL);
		str++;
	}
	return (str);
}
