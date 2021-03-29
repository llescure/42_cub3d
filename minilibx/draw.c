#include "../include/struct_cub3D.h"
#include "../include/cub3D.h"

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

int	draw_square(float i, float j, t_data *data, int color)
{
	t_rect rect;
	int width;
	int lenght;

	lenght = data->param.resolution.axe_x / 20;
	width = data->param.resolution.axe_x / 20;
	rect.x = 15 + lenght * j;
	rect.y = 15 + width * i;
	rect.width = lenght - 1;
	rect.height = width - 1;
	rect.color = color;
	if (data->win_ptr == NULL)
		return (1);
	draw_rect(&data->img_minimap, rect);
	if (color == 0xFD6C9E)
		draw_line(data, rect);
	return (0);
}

int	draw_line(t_data *data, t_rect rect)
{
	int dist;
	int lenght;
	int	x;
	int y;

	lenght = data->param.resolution.axe_x / 15;
	dist = 0;
	while (dist < lenght)
	{
		x = rect.x + rect.width / 2 + dist * cos(data->param.perso.angle *
				M_PI / 180);
		y = rect.y + rect.width / 2 + dist * sin(data->param.perso.angle *
				M_PI / 180);
		img_pix_put(&data->img_minimap, x, y, RED_PIXEL);
		dist++;
	}
	return (0);
}

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
			if (data->param.map.tab_map[i][j] == '2')
				draw_square(i, j, data, GREEN_PIXEL);
			else if (data->param.map.tab_map[i][j] != '1')
				draw_square(i, j, data, BLUE_PIXEL);
			j++;
		}
		i++;
	}
	i = data->param.perso.position_y;
	j = data->param.perso.position_x;
	draw_square(i, j, data, 0xFD6C9E);
	return (0);
}
