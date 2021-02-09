/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 15:51:35 by slescure          #+#    #+#             */
/*   Updated: 2021/02/09 15:58:16 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static	int		nb_of_parts(char const *s, char c)
{
	int i;
	int t;

	i = 0;
	t = 0;
	while (s[i] != 0)
	{
		if ((i == 0 || s[i - 1] == c) && s[i] != c)
			t++;
		i++;
	}
	return (t);
}

static	int		fill_str(char **ptr, int t, char const *s, int *tab)
{
	int x;

	ptr[t] = malloc(sizeof(char) * (tab[1] + 1));
	x = 0;
	while (x < tab[1])
	{
		ptr[t][x] = s[tab[0] - tab[1] + x];
		x++;
	}
	ptr[t][tab[1]] = 0;
	t++;
	return (t);
}

static	int		fill_tab(char const *s, char c, char **ptr)
{
	int m;
	int i;
	int t;
	int tab[2];

	t = 0;
	i = 0;
	while (s[i])
	{
		m = 0;
		while (s[i] == c && s[i])
			i++;
		while (s[i] != c && s[i])
		{
			i++;
			m++;
		}
		if (m)
		{
			tab[0] = i;
			tab[1] = m;
			t = fill_str(ptr, t, s, tab);
		}
	}
	return (t);
}

char			**ft_split(char const *s, char c)
{
	int		t;
	char	**ptr;

	t = nb_of_parts(s, c);
	if (!(ptr = (char **)malloc((t + 1) * sizeof(char *))))
		return (NULL);
	t = fill_tab(s, c, ptr);
	ptr[t] = NULL;
	return (ptr);
}
