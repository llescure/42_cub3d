#include "../include/struct_cub3d.h"
#include "../include/cub3d.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char *pixel;

	pixel = img->addr + (y * img->line_lenght + x * (img->bits_per_pixel / 8));
	*(int *)pixel = color;
}

int		draw_rect(t_img *img, t_rect rect)
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

int		draw_square(float i, float j, t_data *data, int color)
{
	t_rect	rect;
	int		lenght;

	lenght = initialize_max_res(data);
	rect.x = lenght * j;
	rect.y = lenght * i;
	rect.width = lenght;
	rect.height = lenght;
	rect.color = color;
	if (data->win_ptr == NULL)
		return (1);
	draw_rect(&data->img, rect);
	if (color == PINK_PIXEL)
		draw_line(data, rect);
	return (0);
}

int		initialize_max_res(t_data *data)
{
	int		max_res;
	int		max_lines;
	int		lenght;

	if (data->param.resolution.axe_y > data->param.resolution.axe_x)
		max_res = data->param.resolution.axe_x;
	else
		max_res = data->param.resolution.axe_y;
	if (data->param.map.nb_lines > data->param.map.max_length)
		max_lines = data->param.map.nb_lines;
	else
		max_lines = data->param.map.max_length;
	if (max_lines > max_res / (max_res / 68))
		lenght = max_lines / (max_res / 68);
	else
		lenght = max_res / (max_lines * 3);
	return (lenght);
}

int		draw_column(int beginning, int end, int pos_x, t_data *data)
{
	int i;

	i = beginning;
	if (data->ray.hit == 1)
		draw_texture_walls(data, pos_x);
	if (data->ray.hit == 2)
	{
		while (i < end)
		{
			img_pix_put(&data->img, pos_x, i, GREEN_PIXEL *
					data->texture.shade);
			i++;
		}
	}
	return (0);
}
