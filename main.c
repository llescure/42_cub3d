#include "include/struct_cub3D.h"
#include "include/cub3D.h"

int     main(int argc, char **argv)
{
	t_data	data;

	data.param = initialize(argc, argv);
	initialisation_orientation(&data.param, &data.ray);
	if(create_window(&data) == -1)
		return (-1);
	initialize_mlx(&data);
	return (0);
}
