/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 14:07:11 by slescure          #+#    #+#             */
/*   Updated: 2021/02/05 15:57:06 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	ft_strlen(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char		*ft_strjoin(char *s1, char *s2)
{
	size_t		i;
	size_t		j;
	char		*dest;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	dest = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (dest == NULL)
		return (NULL);
	dest[ft_strlen(s1) + ft_strlen(s2)] = '\0';
	i = -1;
	while (s1[++i] != '\0')
		dest[i] = s1[i];
	j = 0;
	while (s2[j] != '\0')
		dest[i++] = s2[j++];
	dest[i] = '\0';
	return (dest);
}

int     main(int argc, char **argv)
{
    char *str;
    char *map;
    int r;
    int tmp;
    int fd;

    r = 1;
    tmp = 0;
    map = "";
    if (!(str = malloc(sizeof(char) * 11)))
        return (-1);
    fd = open(argv[1], O_RDONLY);

    if (argc != 2 && argc != 3)
    {
        perror("ERROR : wrong number of arguments");
        return (-1);
    }
    while ((r = read(fd, str, 10)) > 0)
    {
        str[r] = '\0';
        tmp = r + tmp;
        map = ft_strjoin(map, str);
    }
    parsing_map(map);
    free(map);
    free(str);
    return (0);
}
