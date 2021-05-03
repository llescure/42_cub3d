/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/17 23:20:35 by llescure          #+#    #+#             */
/*   Updated: 2021/01/06 10:08:55 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void				ft_free(char **s, unsigned long pos)
{
	while (pos > 0)
	{
		pos--;
		free(s[pos]);
	}
	free(s);
}

unsigned long		ft_count_words(char const *s, char sep)
{
	unsigned long i;
	unsigned long compt;

	i = 0;
	compt = 0;
	while (s[i] != '\0')
	{
		if (s[i] != sep && (s[i + 1] == sep || (s[i + 1] == '\0')))
			compt++;
		if (s[i + 1] == '\0')
			break ;
		i++;
	}
	return (compt);
}

unsigned long		ft_cara(char const *s, char sep, int pos)
{
	unsigned long i;
	unsigned long compt;

	i = pos;
	compt = 0;
	while (s[i] == sep)
		i++;
	while (s[i] != sep && s[i] != '\0')
	{
		compt++;
		i++;
	}
	return (compt);
}

char				**ft_split(char const *s, char c)
{
	char						**tab;
	unsigned long				i;
	unsigned long				pos;

	i = 0;
	pos = 0;
	if (!(tab = malloc(sizeof(char *) * (ft_count_words(s, c) + 1))))
		return (NULL);
	while (i < ft_count_words(s, c))
	{
		if (!(tab[i] = (char *)malloc(sizeof(char) * (ft_cara(s, c, pos) + 1))))
		{
			ft_free(tab, i);
			return (NULL);
		}
		while (s[pos] == c)
			pos++;
		ft_memcpy(tab[i], s + pos, ft_cara(s, c, pos));
		tab[i][ft_cara(s, c, pos)] = '\0';
		pos += ft_cara(s, c, pos);
		i++;
	}
	tab[i] = NULL;
	return (tab);
}
