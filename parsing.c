/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slescure <slescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 14:07:11 by slescure          #+#    #+#             */
/*   Updated: 2021/02/03 08:43:06 by slescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int     calculate_nb_chains(char *str)
{
    int i;
    int n;

    i = 0;
    n = 1;
    while (str[i] != '\0')
    {
        if str[i] == '\n')
            n++;
        i++;
    }
    return (n);
}

int     ft_biggestlinelen(char *str)
{
    int i;
    int j;
    int result;

    i = 0;
    j = 0;
    result = j;
    while (str[i] != '\0')
    {
        while (str[j] != '\n')
            j++;
        if (j > result)
            result = j;
        j = 0;
    }
    return (result);
}

int     parsing(char *str)
{
    char    **liste;
    int     i;

    i = 0;
    liste = malloc(sizeof(char*) * calculate_nb_chains(str));
    liste[i] = malloc(sizeof(char) * ft_biggestlinelen(str));
}

int     verif_wall(char *str)
{
    int result;
    int i;

    result = 0;
    i = 0;
    if (str[0] != 1 || str[ft_strlen(str) - 1] != 1)
    {
        perror("ERROR : wrong format of the map");
        return (-1);
    }
    while (str[i] != '\0')
    {
        if (str[i] != '1' || str[i] != '0'|| str[i] != '2' || str[i] != 'E')
        {
            perror("ERROR : wrong symbol in the map");
            return (-1);
        }
        i++;
    }
    return (0);
}

int verif_typo(char *str)
{

}

int     verif_map(char *str)
{

}
