/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 17:33:32 by slescure          #+#    #+#             */
/*   Updated: 2019/10/16 15:24:30 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *chaine, int car)
{
	char	*str;
	int		i;

	str = (char *)chaine;
	i = ft_strlen(str);
	while (str[i] != car)
	{
		if (i == 0)
			return (NULL);
		i--;
	}
	return (str + i);
}
