#include "include/struct_cub3D.h"
#include "include/cub3D.h"

int     main(int argc, char **argv)
{
	t_data	data;

	data.param = initialize(argc, argv);
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
	{
		printf("ERROR\nCouldn't start mlx_init");
		return (-1);
	}
	data.win_ptr = mlx_new_window(data.mlx_ptr, data.param.resolution.axe_x,
			data.param.resolution.axe_y, "my window");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		printf("ERROR\nCouldn't open a window");
		return (-1);
	}
	//raycasting(&data);
	initialize_mlx(&data);
	return (0);
}
