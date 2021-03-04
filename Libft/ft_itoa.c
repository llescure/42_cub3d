/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 16:00:14 by slescure          #+#    #+#             */
/*   Updated: 2019/10/20 19:35:53 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int			ft_longueur(int n)
{
	int			l;

	if (n <= 0)
		l = 1;
	else
		l = 0;
	while (n != 0)
	{
		n = n / 10;
		l++;
	}
	return (l);
}

char		*ft_itoa(int n)
{
	long				sign;
	long				len;
	long				nb;
	char				*str;

	sign = (n < 0 ? 1 : 0);
	str = NULL;
	len = ft_longueur(n);
	nb = (long)n;
	if (sign == 1)
		nb = -nb;
	if (!(str = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	str[len--] = '\0';
	while (len >= 0)
	{
		str[len] = nb % 10 + '0';
		nb = nb / 10;
		len--;
	}
	if (sign == 1)
		str[0] = '-';
	return (str);
}
