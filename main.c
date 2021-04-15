#include "include/struct_cub3d.h"
#include "include/cub3d.h"

int		main(int argc, char **argv)
{
	t_data	data;

	data.param = initialize(argc, argv);
	if (argc == 3 && ft_strncmp(argv[2], "--save", ft_strlen(argv[2])) == 0)
		return (create_image(&data));
	if (create_window(&data) == -1)
		return (-1);
	initialize_mlx(&data);
	return (0);
}
