char     **recup_map(char **str, int largeur, int longueur)
{
    int i;

    i = 0;
    char result[largeur][longueur];

    while(str[largeur][0] != 1)
        largeur++;
    while(str[largeur][0] == 1)
    {
        result[i] = ft_strcpy(result[i], str[largeur]);
        largeur++;
        i++;
    }
    return(result);
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
        if (str[i] != '0' || str[i] != '1'|| str[i] != '2' || str[i] != 'E')
        {
            perror("ERROR : wrong symbol in the map");
            return (-1);
        }
        i++;
    }
    return (0);
}
