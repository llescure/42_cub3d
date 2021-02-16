/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verification_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 14:29:35 by slescure          #+#    #+#             */
/*   Updated: 2021/02/08 17:06:01 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int     check_end_walls(char *str, int length) // good
{
    int result;
    int i;

    result = 0;
    i = 0;
    length = length - 2; // pk deja ???
    while (str[i] == '5')
        i++;
    if (str[i] != '1')
    {
        perror("ERROR : wrong format of the map : pas de murs en extremite");
        exit(0);
    }
    while (str[length] == '5')
        length--;
    if (str[length] != '1')
    {
        perror("ERROR : wrong format of the map : pas de murs en extremite");
        exit(0);
    }
	return (0);
}

int     perso_orientation_position(char *str, t_param *param)
{
    char    result;
    int     nb_result;
    int     position;
    int		i;

    nb_result = 0;
	position = 0;
	i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == 'N' || str[i] == 'S' || str[i] == 'E' || str[i] == 'W')
        {
            result = str[i];
            position = i;
            nb_result++;
        }
        i++;
    }
    if (nb_result > 1)
    {
        perror("ERROR : too many characters in the map");
        exit (0);
    }
	if (position != 0)
	{
		param->perso.position_x = position;
		param->perso.orientation = result;
	}
    return (nb_result);
}

int		check_symbols(char *str)
{
	int i;

	i = 0;
//	printf("str = %s\n", str);
    while (str[i] != '\0')
    {
        if (str[i] != '0' && str[i] != '1' && str[i] != '2' && str[i] != 'E'
            && str[i] != 'S' && str[i] != 'W' && str[i] != 'N' && str[i] != '5'
			&& str[i] != ' ')
        {
//			printf("str[%i] = %c\n", i, str[i]);
            perror("ERROR : wrong symbol in the map");
            exit (0);
        }
        i++;
    }
    return (0);
}

char     *check_space_in_map(char *str)
{
    int i;

    i = 0;
    while (str[i] != '\0')
    {
        if (str[i] == '5')
            str[i] = '1';
        i++;
    }
    return (str);
}

int     check_holes_walls(char **map, int nb_lines, int length)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < nb_lines)
    {
        while (j < length)
        {
            if ((map[i][j] == '0') && (map[i+1][j] == '5'))
            {
                perror("ERROR : wrong format of the map : trous dans la map");
                exit (0);
            }
            j++;
        }
        j = 0;
        i++;
    }
    return (0);
}

int     check_first_last_string_map(char *str)
{
    int i;

    i = -1;
    while (str[++i] != '\0')
    {
        if (str[i] != '1' && str[i] != '5')
        {
            perror("ERROR : wrong format of the map : espace vide en extremite");
            exit (0);
        }
        if (str[i] == '1' && str[i + 1] == '5' && str[i + 2] == '1')
        {
            perror("ERROR : wrong format of the map : espace vide en extremite");
            exit (0);
        }
    }
    return (0);
}

int     check_map(char **map, int nb_lines, int max_length, t_param *param)
{
    int i;
	int result;

    i = 0;
	result = 0;
//	printf("map[0] = %s\n", map[0]);
	while (i < nb_lines)
	{
		printf("map[%i] = %s\n", i, map[i]);
		i++;
	}
	i = -1;
    while (++i < nb_lines)
	{
//		printf("liste[%i] = %s\n", i, liste[i]);
        check_end_walls(map[i], max_length);
		check_symbols(map[i]);
	}
    check_first_last_string_map(map[0]);
    check_first_last_string_map(map[nb_lines - 1]);
    check_holes_walls(map, nb_lines, max_length);
    i = -1;
    while (++i < nb_lines)
        map[i] = check_space_in_map(map[i]);
	i = 0;
	while (i < nb_lines)
	{
        if (perso_orientation_position(map[i], param) == 1)
		{
            param->perso.position_y = i;
			result++;
		}
        i++;
    }
	if (result != 1)
	{
		perror("ERROR : wrong number of characters on the map");
		exit (0);
	}
	printf("%sCHARACTER : [OK]\n", KGRN);
    printf("%sMAP : [OK]\n", KGRN);
    return (0);
}
