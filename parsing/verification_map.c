/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verification_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 14:29:35 by slescure          #+#    #+#             */
/*   Updated: 2021/02/05 15:45:53 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int     verif_walls_extremite_and_symbols(char *str, int longueur) // good
{
    int result;
    int i;

    result = 0;
    i = 0;
    longueur = longueur - 2;
    while (str[i] == '5')
        i++;
    if (str[i] != '1')
    {
        perror("ERROR : wrong format of the map : pas de murs en extremite");
        exit(0);
    }
    while (str[longueur] == '5')
        longueur--;
    if (str[longueur] != '1')
    {
        perror("ERROR : wrong format of the map : pas de 1 en extremite");
        exit(0);
    }
    while (i < longueur + 1)
    {
        if (str[i] != '0' && str[i] != '1'&& str[i] != '2' && str[i] != 'E'
            && str[i] != 'S' && str[i] != 'W' && str[i] != 'N' && str[i] != '5')
        {
            perror("ERROR : wrong symbol in the map");
            exit (0);
        }
        i++;
    }
    return (0);
}

char     *verif_espace_map(char *str) // ne pas le faire pour liste[0] et liste[largeur -1]
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

int     verif_holes_walls(char **map, int largeur, int longueur)
{
    int i;
    int j;

    i = 0;
    j = 0;
    while (i < largeur)
    {
        while (j < longueur)
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

int     verif_first_last_string_map(char *str)
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
        if (str[i] == '1' && str[i+1] == '5' && str[i+2] == '1')
        {
            perror("ERROR : wrong format of the map : espace vide en extremite");
            exit (0);
        }
    }
    return (0);
}

int     verification_map(char **liste, int largeur, int max_length)
{
    int i;

    i = -1;
    while (++i < largeur)
        verif_walls_extremite_and_symbols(liste[i], max_length);
    verif_first_last_string_map(liste[0]);
    verif_first_last_string_map(liste[largeur - 1]);
    verif_holes_walls(liste, largeur, max_length);
    i = -1;
    while (++i < largeur)
        liste[i] = verif_espace_map(liste[i]);
    printf("MAP WALLS : [OK]\n");
    return (0);
}
