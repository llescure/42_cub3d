#include "parsing.h"

int		manage_errors(int argc, char **argv)
{
	int		i;
	char	*s1;

	s1 = "--save";
	i = 0;
	if (argc != 2 && argc != 3)
	{
		perror("ERROR\nWrong number of arguments");
		exit(0);
	}
	if (argc == 3 && (ft_is_string(argv[2], s1) == 0))
	{
		perror("ERROR\nWrong third argument");
		exit(0);
	}
	file_is_cub(argv[1]);
	return (0);
}

int		file_is_cub(char *str)
{
	int i;

	i = 0;
	while (str[i] != '.')
		i++;
	i++;
	if (str[i] == 'c' && str[i + 1] == 'u' && str[i + 2] == 'b'
			&& str[i + 3] == '\0')
		return (1);
	else
	{
		perror("ERROR\nWrong format of file");
		exit(0);
	}
	return (0);
}
