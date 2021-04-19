#include "../include/struct_cub3d.h"
#include "../include/cub3d.h"

void	convert_health_level(t_data *data)
{
	if (!(data->bonus.tab_life[0].img = mlx_xpm_file_to_image(data->mlx_ptr,
					"./bonus/1_life.xpm", &(data->bonus.tab_life[0].width),
					&(data->bonus.tab_life[0].height))))
		exit (0);
	if (!(data->bonus.tab_life[1].img = mlx_xpm_file_to_image(data->mlx_ptr,
					"./bonus/2_life.xpm", &(data->bonus.tab_life[1].width),
					&(data->bonus.tab_life[1].height))))
		exit (0);
	if (!(data->bonus.tab_life[2].img = mlx_xpm_file_to_image(data->mlx_ptr,
					"./bonus/3_life.xpm", &(data->bonus.tab_life[2].width),
					&(data->bonus.tab_life[2].height))))
		exit (0);
	if (!(data->bonus.tab_life[3].img = mlx_xpm_file_to_image(data->mlx_ptr,
					"./bonus/4_life.xpm", &(data->bonus.tab_life[3].width),
					&(data->bonus.tab_life[3].height))))
		exit (0);
}

void	get_health_level(t_data *data)
{
	convert_health_level(data);
	data->bonus.tab_life[0].addr = mlx_get_data_addr(data->bonus.tab_life[0].img,
			&data->bonus.tab_life[0].bits_per_pixel,
			&data->bonus.tab_life[0].line_lenght,
			&data->bonus.tab_life[0].endian);
	data->bonus.tab_life[1].addr = mlx_get_data_addr(data->bonus.tab_life[1].img,
			&data->bonus.tab_life[1].bits_per_pixel,
			&data->bonus.tab_life[1].line_lenght,
			&data->bonus.tab_life[1].endian);
	data->bonus.tab_life[2].addr = mlx_get_data_addr(data->bonus.tab_life[2].img,
			&data->bonus.tab_life[2].bits_per_pixel,
			&data->bonus.tab_life[2].line_lenght,
			&data->bonus.tab_life[2].endian);
	data->bonus.tab_life[3].addr = mlx_get_data_addr(data->bonus.tab_life[3].img,
			&data->bonus.tab_life[3].bits_per_pixel,
			&data->bonus.tab_life[3].line_lenght,
			&data->bonus.tab_life[3].endian);
}

int	health_management(t_data *data)
{
	get_health_level(data);
	if (data->bonus.life == 4)
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->bonus.tab_life[3].img, 0, data->param.resolution.axe_y - 75);
	else if (data->bonus.life == 3)
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->bonus.tab_life[2].img, 0, data->param.resolution.axe_y - 75);
	else if (data->bonus.life == 2)
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->bonus.tab_life[1].img, 0, data->param.resolution.axe_y - 75);
	else if (data->bonus.life == 1)
			mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->bonus.tab_life[0].img, 0, data->param.resolution.axe_y - 75);
	if (data->bonus.life == 0)
	{
		print_error(&data->param, "Game over");
		return (-1);
	}
	return (0);
}
