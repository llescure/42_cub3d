#include "minilibx.h"

int		press_key(int key, t_data *data)
{
	if (key == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	return (0);
}

int     main(void)
{
	t_data	data;
	t_img	img;

	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, 1920, 1080, "my window");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (1);
	}
//	img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
//	mlx_put_image_to_window(data.mlx_ptr, data.win_ptr, img, 600, 400);
//	mlx_loop_hook(data.mlx_ptr, press_key, (void *) 0);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &press_key, &data);
	mlx_loop(data.mlx_ptr);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
}
