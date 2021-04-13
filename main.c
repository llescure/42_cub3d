#include "include/struct_cub3d.h"
#include "include/cub3d.h"

int		main(int argc, char **argv)
{
	t_data	data;

	data.param = initialize(argc, argv);
	initialisation_orientation(&data.param, &data.ray);
	if (argv[2] == "--save")
	{
		if (create_image(&data) == -1)
		{
			free_address_params(&data->param);
			return (-1);
		}
		else
			return (0);
	}
	if (create_window(&data) == -1)
		return (-1);
	initialize_mlx(&data);
	return (0);
}
