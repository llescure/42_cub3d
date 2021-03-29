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
	data.img_minimap.img = mlx_new_image(data.mlx_ptr, data.param.resolution.axe_x,
			data.param.resolution.axe_y);
	data.img_main.img = mlx_new_image(data.mlx_ptr, data.param.resolution.axe_x,
			data.param.resolution.axe_y);
	data.img_minimap.addr = mlx_get_data_addr(data.img_minimap.img, &data.img_minimap.bits_per_pixel,
			&data.img_minimap.line_lenght, &data.img_minimap.endian);
	data.img_main.addr = mlx_get_data_addr(data.img_main.img, &data.img_main.bits_per_pixel,
			&data.img_main.line_lenght, &data.img_minimap.endian);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &press_key, &data);
	mlx_hook(data.win_ptr, 33, (1L << 17), &click_close, &data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &release_key, &data);
	mlx_loop_hook(data.mlx_ptr, &launch_hook, &data);
	mlx_loop(data.mlx_ptr);
	mlx_destroy_image(data.mlx_ptr, data.img_minimap.img);
//	mlx_destroy_image(data.mlx_ptr, data.img_main.img);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	return (0);
}
