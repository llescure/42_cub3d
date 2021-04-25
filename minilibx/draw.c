#include "../include/struct_cub3d.h"
#include "../include/cub3d.h"

int		draw_floor(int beginning, int end, int pos_x, t_data *data)
{
	int i;
	int color;

	if (data->param.floor_texture != NULL)
	{
		draw_texture_floor(data, pos_x);
		return (0);
	}
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

	if (data->param.ceiling_texture != NULL)
	{
		draw_texture_ceiling(data, pos_x);
		return (0);
	}
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
					draw_square(i, j, data, RED_PIXEL);
				else if (data->param.map.tab_map[i][j] == '3')
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
