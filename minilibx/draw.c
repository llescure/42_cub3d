#include "../include/struct_cub3D.h"
#include "../include/cub3D.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char *pixel;

	pixel = img->addr + (y * img->line_lenght +  x * (img->bits_per_pixel / 8));
	*(int *)pixel = color;
}

int	draw_rect(t_img *img)
{
	int i;
	int j;

	i = img->rect.y;
	while (i < img->rect.y + img->rect.height)
	{
		j = img->rect.x;
		while (j < img->rect.x + img->rect.width)
		{
			img_pix_put(img, j, i, img->rect.color);
			j++;
		}
		i++;
	}
	return (0);
}

int	draw_square(int i, int j, t_data *data, int color)
{
	int width;
	int lenght;

	lenght = 200 / (data->param.map.max_length - 2);
	width = 200 / (data->param.map.nb_lines - 2);
	data->img.rect.x = 15 + lenght * j;
	data->img.rect.y = 15 + width * i;
	data->img.rect.width = lenght;
	data->img.rect.height = width;
	data->img.rect.color = color;
	if (data->win_ptr == NULL)
		return (1);
	draw_rect(&data->img);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
	return (0);
}

/*int	draw_column(int start, int end, t_data *data, int color)
{
	int		i;

	i = start;
	while (i < end)
	{
		img_pix_put(img, j, i, rect.color);
		i++;
	}
	return (0);
}*/

int	draw_minimap(t_data *data)
{
	int		i;
	int		j;

	i = 0;
	while (i < data->param.map.nb_lines)
	{
		j = 0;
		while (j < data->param.map.max_length)
		{
			if (data->param.map.map[i][j] == '0')
				draw_square(i, j, data, BLUE_PIXEL);
			else if (data->param.map.map[i][j] == '2')
				draw_square(i, j, data, GREEN_PIXEL);
			else if (data->param.map.map[i][j] == 'N')
				draw_square(i, j, data, 0xFD6C9E);
			j++;
		}
		i++;
	}
	return (0);
}