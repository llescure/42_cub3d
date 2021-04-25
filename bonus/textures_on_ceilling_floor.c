#include "../include/struct_cub3d.h"
#include "../include/cub3d.h"

void	get_ceiling_textures(t_data *data)
{
	if (!(data->tab_texture[4].img = mlx_xpm_file_to_image(data->mlx_ptr,
					data->param.ceiling_texture, &(data->tab_texture[4].width),
					&(data->tab_texture[4].height))))
		exit (0);
	data->tab_texture[4].addr = mlx_get_data_addr(data->tab_texture[4].img,
			&data->tab_texture[4].bits_per_pixel, &data->tab_texture[4].
			line_lenght, &data->tab_texture[4].endian);
}

void	get_floor_textures(t_data *data)
{
	if (!(data->tab_texture[5].img = mlx_xpm_file_to_image(data->mlx_ptr,
					data->param.floor_texture, &(data->tab_texture[5].width),
					&(data->tab_texture[5].height))))
		exit (0);
	data->tab_texture[5].addr = mlx_get_data_addr(data->tab_texture[5].img,
			&data->tab_texture[5].bits_per_pixel, &data->tab_texture[5].
			line_lenght, &data->tab_texture[5].endian);
}

void	draw_texture_ceiling(t_data *data, int pos_x)
{
	int y;

	y = 0;
	while (y < data->ray.draw_start)
	{
		data->img.addr[pos_x * 4 + 4 * data->param.resolution.axe_x * y] =
			data->tab_texture[4].addr[pos_x * 4 + 4 *
			data->tab_texture[4].width * y];
		data->img.addr[pos_x * 4 + 4 * data->param.resolution.axe_x * y + 1] =
			data->tab_texture[4].addr[pos_x * 4 + 4 *
			data->tab_texture[4].width * y + 1];
		data->img.addr[pos_x * 4 + 4 * data->param.resolution.axe_x * y + 2] =
			data->tab_texture[4].addr[pos_x * 4 + 4 *
			data->tab_texture[4].width * y + 2];
		data->img.addr[pos_x * 4 + 4 * data->param.resolution.axe_x * y + 3] =
			data->tab_texture[4].addr[pos_x * 4 + 4 *
			data->tab_texture[4].width * y + 3];
	y++;
	}
}

void	draw_texture_floor(t_data *data, int pos_x)
{
	int y;
	int z;

	y = data->ray.draw_end;
	z = 0;
	while (y < data->param.resolution.axe_y)
	{
		data->img.addr[pos_x * 4 + 4 * data->param.resolution.axe_x * y] =
			data->tab_texture[5].addr[pos_x * 4 + 4 *
			data->tab_texture[5].width * z];
		data->img.addr[pos_x * 4 + 4 * data->param.resolution.axe_x * y + 1] =
			data->tab_texture[5].addr[pos_x * 4 + 4 *
			data->tab_texture[5].width * z + 1];
		data->img.addr[pos_x * 4 + 4 * data->param.resolution.axe_x * y + 2] =
			data->tab_texture[5].addr[pos_x * 4 + 4 *
			data->tab_texture[5].width * z + 2];
		data->img.addr[pos_x * 4 + 4 * data->param.resolution.axe_x * y + 3] =
			data->tab_texture[5].addr[pos_x * 4 + 4 *
			data->tab_texture[5].width * z + 3];
	y++;
	z++;
	}
}

void	free_textures_bonus(t_data *data)
{
	if (data->param.floor_texture != NULL)
	{
		if (data->tab_texture[4].img)
			mlx_destroy_image(data->mlx_ptr, data->tab_texture[4].img);
	}
	if (data->param.ceiling_texture != NULL)
	{
		if (data->tab_texture[5].img)
			mlx_destroy_image(data->mlx_ptr, data->tab_texture[5].img);
	}
}
