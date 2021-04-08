#include "../include/struct_cub3d.h"
#include "../include/cub3d.h"

int		draw_column(int beginning, int end, int pos_x, t_data *data)
{
	int i;

	i = beginning;
	if (data->ray.hit == 1)
	{
		while (i < end)
		{
			data->texture.y = (int)data->texture.position & (data->texture.text_height - 1);
			data->texture.position += data->texture.step;
//			data->img.addr[(i * (int)data->param.resolution.axe_x + i)] = data->texture.color[(data->texture.y * data->texture.text_height + data->texture.x)];
			img_pix_put(&data->img, pos_x, i, GREY_PIXEL * data->texture.shade);
			i++;
		}
	}
	if (data->ray.hit == 2)
	{
		while (i < end)
		{
			data->texture.y = (int)data->texture.position & (data->texture.text_height - 1);
			data->texture.position += data->texture.step;
//			data->img.addr[(i * (int)data->param.resolution.axe_x + i)] = data->texture.color[(data->texture.y * data->texture.text_height + data->texture.x)];
			img_pix_put(&data->img, pos_x, i, GREEN_PIXEL * data->texture.shade);
			i++;
		}
	}
	return (0);
}

int		draw_floor(int beginning, int end, int pos_x, t_data *data)
{
	int i;
	int color;

	color = conversion_rgb_to_hexa(data->param.floor_colour);
	i = beginning;
	while (i < end)
	{
		img_pix_put(&data->img, pos_x, i, color);
		i++;
	}
	return (0);
}

int		draw_ceiling(int beginning, int end, int pos_x, t_data *data)
{
	int i;
	int color;

	color = conversion_rgb_to_hexa(data->param.ceiling_colour);
	i = beginning;
	while (i < end)
	{
		img_pix_put(&data->img, pos_x, i, color);
		i++;
	}
	return (0);
}

int		draw_line(t_data *data, t_rect rect)
{
	int dist;
	int lenght;
	int	x;
	int y;

	lenght = rect.width;
	dist = 0;
	while (dist < lenght)
	{
		x = rect.x + rect.width / 2 + dist * cos(data->param.perso.angle *
				M_PI / 180);
		y = rect.y + rect.height / 2 + dist * sin(data->param.perso.angle *
				M_PI / 180);
		img_pix_put(&data->img, x, y, RED_PIXEL);
		dist++;
	}
	return (0);
}

int		draw_minimap(t_data *data)
{
	int		i;
	int		j;

	i = 0;
	while (i < data->param.map.nb_lines)
	{
		j = 0;
		while (j < data->param.map.max_length - 1)
		{
			if (data->param.map.tab_map[i][j] == '2')
				draw_square(i, j, data, GREEN_PIXEL);
			else if (data->param.map.tab_map[i][j] == '0')
				draw_square(i, j, data, BLUE_PIXEL);
			else if (data->param.map.tab_map[i][j] == '1')
				draw_square(i, j, data, GREY_PIXEL);
			j++;
		}
		i++;
	}
	i = data->param.perso.position_y;
	j = data->param.perso.position_x;
	draw_square(i, j, data, PINK_PIXEL);
	return (0);
}
