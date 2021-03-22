#include "include/struct_cub3D.h"
#include "include/cub3D.h"

int     main(int argc, char **argv)
{
	t_data	data;
	t_ray	ray;

	data.param = initialize(argc, argv, &ray);
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
	{
		printf("ERROR\nCouldn't start mlx_init");
		return (-1);
	}
	data.win_ptr = mlx_new_window(data.mlx_ptr, 1920, 1080, "my window");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		printf("ERROR\nCouldn't open a window");
		return (-1);
	}
	data.img.img = mlx_new_image(data.mlx_ptr, 1920, 1080);
	data.img.addr = mlx_get_data_addr(data.img.img, &data.img.bits_per_pixel,
			&data.img.line_lenght, &data.img.endian);
	mlx_loop_hook(data.mlx_ptr, &draw_minimap, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &press_key, &data);
	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &release_key, &data);
	mlx_hook(data.win_ptr, 33, (1L << 17), &click_close, &data);
	mlx_loop(data.mlx_ptr);
	mlx_destroy_image(data.mlx_ptr, data.img.img);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	return (0);
}
