/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verification_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 14:29:35 by slescure          #+#    #+#             */
/*   Updated: 2021/02/04 16:00:24 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int     verif_walls_and_symbols(char *str, int longueur) // verifie si entoure de murs et contient les bons symboles
{
    int result;
    int i;

    result = 0;
    i = 0;
    if (str[0] != 1)
    {
        perror("ERROR : wrong format of the map");
        return (-1);
    }
    while (str[longueur] == 5)
            longueur--;
    if (str[longueur] != 1 || str[longueur] != 5)
    {
        perror("ERROR : wrong format of the map");
        return (-1);
    }
//    while (str[i] != '\0')
//    {
//        if (str[i] != '0' || str[i] != '1'|| str[i] != '2' || str[i] != 'E'
//            || str[i] != 'S' || str[i] != 'W' || str[i] != 'N')
//        {
//            perror("ERROR : wrong symbol in the map");
//            return (-1);
//        }
//        i++;
//    }
    return (0);
}

int     calculate_nb_chains(char *str) //good
{
    int result;
    int i;

    i = 0;
    result = 0;
    while (str[i] != '\0')
    {
        i++;
        if (str[i] == '\n')
            result++;
    }
    return (result);
}

int     ft_biggest_line_len(char *str) //good
{
    int i;
    int j;
    int result;

    j = 0;
    i = 0;
    result = 1;
    while (str[i] != '\0')
    {
        while (str[i] != '\n')
        {
            i++;
            j++;
        }
        if (j > result)
            result = j;
        j = 0;
        i++;
    }
    result++;
    return (result);
}

char     *only_map(char *str) //good
{
    int     i;
    int     j;
    int     max_length;
    char    *map;

    i = 0;
    j = 0;
    while (str[i] != '\n' || str[i+2] != '\n')
        i++;
    while (str[i] == '\n')
        i++;
    j = calculate_nb_chains(str);
    max_length = ft_biggest_line_len(str);
    if (!(map = malloc(sizeof(char) * j * max_length)))
        return (NULL);
    j = 0;
    while (str[i] != '\0')
    {
        map[j] = str[i];
        i++;
        j++;
    }
    map[j] = '\0';
    return (map);
}

int     creation_tableau_map(char *str) //good
{
    int     largeur;
    int     longueur;
    int     i;
    int     max_length;
    char    **liste;

    i = 0;
    str = only_map(str);
    largeur = calculate_nb_chains(str);
    max_length = ft_biggest_line_len(str);
    if (!(liste = malloc(sizeof(char*) * largeur)))
        return (-1);
    while (i < largeur)
    {
        if (!(liste[i] = malloc(sizeof(char**) * max_length)))
            return (-1);
        i++;
    }
    largeur = 0;
    longueur = 0;
    i = 0;
    while (str[i] != '\0')
    {
        while (str[i] != '\n')
        {
            liste[largeur][longueur] = str[i];
            longueur++;
            i++;
            if ((str[i] == '\n') && (longueur < max_length - 1))
            {
                while (longueur < max_length - 1)
                {
                    liste[largeur][longueur] = '5';
                    longueur++;
                }
            }
        }
        i++;
        largeur++;
        longueur = 0;
    }
    largeur = 0;
//    while (largeur < 13)
//    {
    printf("liste[0] = %s\n", liste[0]);
        if (verif_walls_and_symbols(liste[0], max_length) == -1)
            return (-1);
//        largeur++;
//    }
    printf("liste[0] = %s\n", liste[0]);
    return (0);
}
