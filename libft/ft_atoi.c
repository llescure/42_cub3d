/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 23:10:04 by llescure          #+#    #+#             */
/*   Updated: 2020/11/02 20:41:37 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_is_white_space(char c)
{
	if (c == ' ' || c == '\t' || c == '\n' ||
		c == '\v' || c == '\f' || c == '\r')
		return (1);
	return (0);
}

long	ft_check_sign(const char *str)
{
	long						sign;
	long						i;

	sign = 1;
	i = 0;
	while (str[i] == '-' || str[i] == '+' || ft_is_white_space(str[i]) == 1)
	{
		if (str[i] == '-')
		{
			if (str[i + 1] == '+' || sign == -1 ||
				ft_is_white_space(str[i + 1]) == 1)
				return (0);
			sign = sign * -1;
		}
		if (str[i] == '+')
		{
			if (sign == -1 || str[i + 1] == '-' || str[i + 1] == '+' ||
				ft_is_white_space(str[i + 1]) == 1)
				return (0);
		}
		i++;
	}
	return (sign);
}

int		ft_atoi(const char *str)
{
	int						i;
	long					rslt;
	long					sign;

	i = 0;
	rslt = 0;
	sign = ft_check_sign(str);
	if (sign == 0)
		return (0);
	while (str[i] == '-' || str[i] == '+' || ft_is_white_space(str[i]) == 1)
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		rslt = rslt * 10 + str[i] - '0';
		i++;
	}
	return (sign * rslt);
}
