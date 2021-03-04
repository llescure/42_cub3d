/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 19:03:14 by slescure          #+#    #+#             */
/*   Updated: 2019/10/20 19:03:07 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_checkset(char c, char const *set)
{
	int i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char		*ft_strtrim(char const *str, char const *set)
{
	char	*dst;
	int		i;
	int		j;
	int		k;

	i = 0;
	if (!str)
		return (NULL);
	while (ft_checkset(str[i], set))
		i++;
	if ((j = ft_strlen(&str[i])) > 0)
		j--;
	while (ft_checkset(str[i + j], set))
		j--;
	j++;
	if (!(dst = (char *)malloc(sizeof(char) * (j + 1))))
		return (NULL);
	k = -1;
	while (++k < j)
		dst[k] = (char)str[i + k];
	dst[k] = '\0';
	return (dst);
}
