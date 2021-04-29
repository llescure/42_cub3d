#include "../include/struct_cub3d.h"
#include "../include/cub3d.h"

void	convert_health_level(t_data *data)
{
	if (!(data->bonus.tab_life[0].img = mlx_xpm_file_to_image(data->mlx_ptr,
			"./bonus/1_life.xpm", &(data->bonus.tab_life[0].width),
			&(data->bonus.tab_life[0].height))))
		exit(0);
	if (!(data->bonus.tab_life[1].img = mlx_xpm_file_to_image(data->mlx_ptr,
			"./bonus/2_life.xpm", &(data->bonus.tab_life[1].width),
			&(data->bonus.tab_life[1].height))))
		exit(0);
	if (!(data->bonus.tab_life[2].img = mlx_xpm_file_to_image(data->mlx_ptr,
			"./bonus/3_life.xpm", &(data->bonus.tab_life[2].width),
			&(data->bonus.tab_life[2].height))))
		exit(0);
	if (!(data->bonus.tab_life[3].img = mlx_xpm_file_to_image(data->mlx_ptr,
			"./bonus/4_life.xpm", &(data->bonus.tab_life[3].width),
			&(data->bonus.tab_life[3].height))))
		exit(0);
}

void	get_health_level(t_data *data)
{
	convert_health_level(data);
	data->bonus.life = 4;
	data->bonus.tab_life[0].addr = mlx_get_data_addr(data->bonus.tab_life[0].
			img, &data->bonus.tab_life[0].bits_per_pixel,
			&data->bonus.tab_life[0].line_lenght,
			&data->bonus.tab_life[0].endian);
	data->bonus.tab_life[1].addr = mlx_get_data_addr(data->bonus.tab_life[1].
			img, &data->bonus.tab_life[1].bits_per_pixel,
			&data->bonus.tab_life[1].line_lenght,
			&data->bonus.tab_life[1].endian);
	data->bonus.tab_life[2].addr = mlx_get_data_addr(data->bonus.tab_life[2].
			img, &data->bonus.tab_life[2].bits_per_pixel,
			&data->bonus.tab_life[2].line_lenght,
			&data->bonus.tab_life[2].endian);
	data->bonus.tab_life[3].addr = mlx_get_data_addr(data->bonus.tab_life[3].
			img, &data->bonus.tab_life[3].bits_per_pixel,
			&data->bonus.tab_life[3].line_lenght,
			&data->bonus.tab_life[3].endian);
}

void	draw_life_bar(t_data *data, int i)
{
	int y;
	int z;

	y = data->param.resolution.axe_y - data->bonus.tab_life[i].height;
	z = 0;
	while (y < data->param.resolution.axe_y)
	{
		put_health_bar_on_image(data, i, y, z);
		y++;
		z++;
	}
}

void	put_health_bar_on_image(t_data *data, int i, int y, int z)
{
	int x;
	int img_cord;
	int bonus_cord;

	x = 0;
	while (x < data->bonus.tab_life[i].width)
	{
		img_cord = x * 4 + 4 * data->param.resolution.axe_x * y;
		bonus_cord = x * 4 + 4 * data->bonus.tab_life[i].width * z;
		if (data->bonus.tab_life[i].addr[bonus_cord])
			data->img.addr[img_cord] = data->bonus.tab_life[i].addr[bonus_cord];
		if (data->bonus.tab_life[i].addr[bonus_cord + 1])
			data->img.addr[img_cord + 1] =
			data->bonus.tab_life[i].addr[bonus_cord + 1];
		if (data->bonus.tab_life[i].addr[bonus_cord + 2])
			data->img.addr[img_cord + 2] =
			data->bonus.tab_life[i].addr[bonus_cord + 2];
		if (data->bonus.tab_life[i].addr[bonus_cord + 3])
			data->img.addr[img_cord + 3] =
			data->bonus.tab_life[i].addr[bonus_cord + 3];
		x++;
	}
}

int		health_management(t_data *data)
{
	if (data->param.resolution.axe_x < 750 &&
			data->param.resolution.axe_y < 750)
		return (0);
	if (data->bonus.life == 4)
		draw_life_bar(data, data->bonus.life - 1);
	else if (data->bonus.life == 3)
		draw_life_bar(data, data->bonus.life - 1);
	else if (data->bonus.life == 2)
		draw_life_bar(data, data->bonus.life - 1);
	else if (data->bonus.life == 1)
		draw_life_bar(data, data->bonus.life - 1);
	else if (data->bonus.life == 0)
	{
		printf("Game over\n");
		return (-1);
	}
	return (0);
}
