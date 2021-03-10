#include "minilibx.h"

#define BLUE_PIXEL 0x0000FF

int	press_exit(int key, t_data *data)
{
	if (key == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	return (0);
}

int	click_close(int button, int x, int y, t_data *data)
{
	if (x == 1920 && y == 0 )
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	return (0);
}

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char *pixel;

	pixel = img->addr + (y * img->line_lenght +  x * (img->bits_per_pixel / 8));
	*(int *)pixel = color;
}

int	draw_rect(t_img *img, t_rect rect)
{
	int i;
	int j;

	i = rect.y;
	while (i < rect.y + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
		{
			img_pix_put(img, j, i, rect.color);
			j++;
		}
		i++;
	}
	return (0);
}

int	draw(t_data *data)
{
	t_rect rect;

	rect.x = 0;
	rect.y = 0;
	rect.width = 500;
	rect.height = 1080;
	rect.color = BLUE_PIXEL;
	if (data->win_ptr == NULL)
		return (1);
	draw_rect(&data->img, rect);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
	return (0);
}

int     main(void)
{
	t_data	data;

	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, 1920, 1080, "my window");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (1);
	}
	data.img.img = mlx_new_image(data.mlx_ptr, 1920, 1080);
	data.img.addr = mlx_get_data_addr(data.img.img, &data.img.bits_per_pixel, &data.img.line_lenght, &data.img.endian);
	mlx_loop_hook(data.mlx_ptr, &draw, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &press_exit, &data);
	mlx_hook(data.win_ptr, ButtonPress, ButtonPressMask, &click_close, &data);
	mlx_loop(data.mlx_ptr);
	mlx_destroy_image(data.mlx_ptr, data.img.img);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
}
