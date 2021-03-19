#include "../include/struct_cub3D.h"
#include "../include/cub3D.h"

int	press_key(int key, t_data *data)
{
	if (key == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
/*	else if (key == ROTATE_LEFT)
	{
	}
	else if (key == ROTATE_RIHT)
	{
	}
	else if (key == FORWARD_W_Z)
		data->param.perso.axe_y - 1
	else if (key == BACK_S_S)
		data->param.perso.axe_y + 1
	else if (key == RIGHT_D_D)
		data->param.perso.axe_x + 1
	else if (key == LEFT_A_Q)
		data->param.perso.axe_x - 1*/
	return (0);
}

/*int	release_key(int key, t_data *data)
{
		else if (key == ROTATE_LEFT)
		{
	}
	else if (key == ROTATE_RIHT)
	{
	}
	else if (key == FORWARD_W_Z)
	{
	}
	else if (key == BACK_S_S)
	{
	}
	else if (key == RIGHT_D_D)
	{
	}
	else if (key == LEFT_A_Q)
	{
	}
	return (0);
}*/

int	click_close(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	data->win_ptr = NULL;
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

	rect.x = 50;
	rect.y = 50;
	rect.width = 500;
	rect.height = 1080;
	rect.color = BLUE_PIXEL;
	if (data->win_ptr == NULL)
		return (1);
	draw_rect(&data->img, rect);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
	return (0);
}

int	draw_square(int i, int j, t_data *data, int color)
{
	t_rect rect;
	int width;
	int lenght;

	lenght = (200 - 20) / data->param.map.max_length;
	width = (200 - 20) / data->param.map.nb_lines;
	rect.x = 25 + lenght * j;
	rect.y = 25 + width * i;
	rect.width = lenght;
	rect.height = width;
	rect.color = color;
	if (data->win_ptr == NULL)
		return (1);
	draw_rect(&data->img, rect);
	printf("coucou\n");
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
	return (0);
}

int	draw_minimap(t_data *data)
{
	t_rect	rect;
	int		i;
	int		j;

	i = 0;
	j = 0;
	rect.x = 15;
	rect.y = 15;
	rect.width = 200;
	rect.height = 200;
	rect.color = 0x808080;
	//printf("nb_lines = %d\n", data->param.map.nb_lines);
	if (data->win_ptr == NULL)
		return (1);
	draw_rect(&data->img, rect);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
	while (i < data->param.map.nb_lines)
	{
		while (j < data->param.map.max_length)
		{
			if (data->param.map.map[i][j] == '0')
				draw_square(i, j, data, BLUE_PIXEL);
			else if (data->param.map.map[i][j] == '2')
				draw_square(i, j, data, GREEN_PIXEL);
			j++;
			printf("yo\n");
		}
		i++;
	}
	exit (0);
	return (0);
}

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
//	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &release_key, &data);
	mlx_hook(data.win_ptr, 33, (1L << 17), &click_close, &data);
	mlx_loop(data.mlx_ptr);
	mlx_destroy_image(data.mlx_ptr, data.img.img);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
}
