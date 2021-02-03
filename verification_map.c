/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verification_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 14:29:35 by slescure          #+#    #+#             */
/*   Updated: 2021/02/03 16:52:45 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int     calculate_nb_chains(char *str) //probleme ici : pas le bon nombre
{
    int i;
    int n;

    i = 0;
    n = 1;
    while (str[i] != '\0')
    {
        if (str[i] == '\n')
            n++;
        i++;
    }
    return (n);
}

int     ft_biggest_line_len(char *str)
{
    int i;
    int j;
    int result;

    i = 0;
    j = 0;
    result = 1;
    while (str[i] != '\0')
    {
        while (str[j] != '\n')
            j++;
        if (j > result)
            result = j;
        j = 0;
        i++;
    }
    result++;
    return (result);
}

int     parsing(char *str)
{
    int     largeur;
    int     longueur;
    int     i;

    i = 0;
    printf("str = %s\n", str);
    while (str[i] != '\n' && str[i+1] != '\n')
        i++;
    while (str[i] == '\n')
        i++;
    largeur = calculate_nb_chains(str);
    printf("largeur = %i\n", largeur);
    longueur = ft_biggest_line_len(str);
    printf("longueur = %i\n", longueur);
    char liste[largeur][longueur];
    largeur = 0;
    longueur = 0;
    while (str[i] != '1')
        i++;
    while (str[i] != '\0')
    {
        while (str[i] != '\n')
        {
            liste[largeur][longueur] = str[i];
            longueur++;
            i++;
        }
        i++;
        largeur ++;
        longueur = 0;
    }
    return (0);
}
