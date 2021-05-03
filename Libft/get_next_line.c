/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 21:49:03 by llescure          #+#    #+#             */
/*   Updated: 2021/05/03 15:13:33 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		return_value(int char_read, char **temp)
{
	if (char_read < 0)
		return (-1);
	if (char_read > 0)
		return (1);
	free(*temp);
	*temp = NULL;
	return (0);
}

int		error_case(int fd, char **line, char **temp, char **buf)
{
	if (fd < 0 || BUFFER_SIZE <= 0 || line == NULL || read(fd, *temp, 0) < 0)
		return (-1);
	if (*temp == NULL)
	{
		if (!(*temp = malloc(sizeof(char))))
			return (-1);
		*temp[0] = '\0';
	}
	if (!(*buf = malloc(sizeof(char) * BUFFER_SIZE + 1)))
		return (-1);
	return (0);
}

char	*copy_to_join(char *temp, char *buf)
{
	char				*cpy;

	cpy = temp;
	temp = ft_strjoin(cpy, buf);
	free(cpy);
	return (temp);
}

char	*copy_to_get_temp(char *temp)
{
	char				*cpy;

	cpy = temp;
	temp = get_temp(temp, '\n');
	free(cpy);
	return (temp);
}

int		get_next_line(int fd, char **line)
{
	char				*buf;
	static char			*temp = NULL;
	int					char_read;

	char_read = 1;
	if (error_case(fd, line, &temp, &buf) < 0)
		return (-1);
	if (!(ft_strchr(temp, '\n')))
	{
		while ((char_read = read(fd, buf, BUFFER_SIZE)) > 0)
		{
			buf[char_read] = '\0';
			temp = copy_to_join(temp, buf);
			if (ft_strchr(buf, '\n'))
				break ;
		}
	}
	free(buf);
	*line = ft_trim(temp, '\n');
	temp = copy_to_get_temp(temp);
	return (return_value(char_read, &temp));
}
