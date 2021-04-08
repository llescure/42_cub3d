#include "../include/struct_cub3d.h"
#include "../include/cub3d.h"

int ft_get_addr_textures(t_data *data)
{
	data->texture.text_width = 64;
	data->texture.text_height = 64;
	if (!(data->texture.text_north = mlx_xpm_file_to_image(data->mlx_ptr,
					data->param.north_texture, &data->texture.text_width, &data->texture.text_width)))
		exit (0);
	if (!(data->texture.text_south = mlx_xpm_file_to_image(data->mlx_ptr,
					data->param.south_texture, &data->texture.text_width, &data->texture.text_width)))
		exit (0);
	if (!(data->texture.text_east = mlx_xpm_file_to_image(data->mlx_ptr,
					data->param.east_texture, &data->texture.text_width, &data->texture.text_width)))
		exit (0);
	if (!(data->texture.text_west = mlx_xpm_file_to_image(data->mlx_ptr,
					data->param.west_texture, &data->texture.text_width, &data->texture.text_width)))
		exit (0);
	if (!(data->texture.sprite = mlx_xpm_file_to_image(data->mlx_ptr,
					data->param.sprite, &data->texture.sprite_width, &data->texture.sprite_height)))
		exit (0);
	return (0);

/*	if (data->tp.tpnb != 0)
	{
	 	if (!(data->tp.tex = mlx_xpm_file_to_image(data->mlx.mlx_ptr,
				data->tp.tpway, &data->sprwidth, &data->sprheight)))
			ft_error(0);
	}
	*/
}

void get_textures(t_data *data)
{
	ft_get_addr_textures(data);
	data->texture.text_north = mlx_get_data_addr(data->texture.text_north,
			&data->img.bits_per_pixel, &data->img.line_lenght, &data->img.endian);
	data->texture.text_south = mlx_get_data_addr(data->texture.text_south,
			&data->img.bits_per_pixel, &data->img.line_lenght, &data->img.endian);
	data->texture.text_east = mlx_get_data_addr(data->texture.text_east,
			&data->img.bits_per_pixel, &data->img.line_lenght, &data->img.endian);
	data->texture.text_west = mlx_get_data_addr(data->texture.text_west,
			&data->img.bits_per_pixel, &data->img.line_lenght, &data->img.endian);
	data->texture.sprite = mlx_get_data_addr(data->texture.sprite,
			&data->img.bits_per_pixel, &data->img.line_lenght, &data->img.endian);
}

void	ft_textures_on_walls(t_data *data)
{
	float	wdatax;

	if (data->ray.side == 0)
	 	wdatax = data->ray.pos_y + data->ray.perp_wall_dist *
			data->ray.ray_diry;
	 else
	 	wdatax = data->ray.pos_x + data->ray.perp_wall_dist *
			data->ray.ray_dirx;
	data->texture.x = (int)(wdatax * data->texture.text_height);
	if (data->ray.side == 0 && data->ray.ray_dirx > 0)
	 	data->texture.x = data->texture.text_width - data->texture.x - 1;
	if (data->ray.side == 1 && data->ray.ray_diry < 0)
	 	data->texture.x = data->texture.text_width - data->texture.x - 1;
	data->texture.step = 1.0 * data->texture.text_height /
		data->ray.line_height;
	data->texture.position = (data->ray.draw_start - data->param.resolution.
			axe_y / 2 + data->ray.line_height / 2) * data->texture.step;
	if (data->ray.side == 0 && (data->ray.map_x > data->ray.pos_x))
		data->texture.color = (int *)data->texture.text_south;
	else if (data->ray.side == 1 && (data->ray.map_y < data->ray.pos_y))
		data->texture.color = (int *)data->texture.text_west;
	else if (data->ray.side == 1 && (data->ray.map_y > data->ray.pos_y))
		data->texture.color = (int *)data->texture.text_east;
	else
		data->texture.color = (int *)data->texture.text_north;
	data->texture.color = (int *)data->texture.sprite;
}
