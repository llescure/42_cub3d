#include "../include/struct_cub3d.h"
#include "../include/cub3d.h"

int ft_get_addr_textures(t_data *data)
{
	data->img.width = 64;
	data->img.height = 64;
	if (!(data->tab_texture[0].img = mlx_xpm_file_to_image(data->mlx_ptr,
					data->param.north_texture, &data->texture.text_width, &data->texture.text_height)))
		exit (0);
	if (!(data->tab_texture[1].img = mlx_xpm_file_to_image(data->mlx_ptr,
					data->param.south_texture, &data->texture.text_width, &data->texture.text_width)))
		exit (0);
	if (!(data->tab_texture[2].img = mlx_xpm_file_to_image(data->mlx_ptr,
					data->param.east_texture, &data->texture.text_width, &data->texture.text_width)))
		exit (0);
	if (!(data->tab_texture[3].img = mlx_xpm_file_to_image(data->mlx_ptr,
					data->param.west_texture, &data->texture.text_width, &data->texture.text_width)))
		exit (0);
	if (!(data->tab_texture[4].img = mlx_xpm_file_to_image(data->mlx_ptr,
					data->param.sprite, &data->texture.sprite_width, &data->texture.sprite_height)))
		exit (0);
	return (0);
}

void get_textures(t_data *data)
{
	ft_get_addr_textures(data);
	data->tab_texture[0].addr = (char *)mlx_get_data_addr(data->tab_texture[0].img,
			&data->tab_texture[0].bits_per_pixel, &data->tab_texture[0].line_lenght, &data->tab_texture[0].endian); // NORTH
	data->tab_texture[1].addr = (char *)mlx_get_data_addr(data->tab_texture[1].img,
			&data->tab_texture[1].bits_per_pixel, &data->tab_texture[1].line_lenght, &data->tab_texture[1].endian); // SOUTH
	data->tab_texture[2].addr = (char *)mlx_get_data_addr(data->tab_texture[2].img,
			&data->tab_texture[2].bits_per_pixel, &data->tab_texture[2].line_lenght, &data->tab_texture[2].endian);	// EAST
	data->tab_texture[0].addr = (char *)mlx_get_data_addr(data->tab_texture[3].img,
			&data->tab_texture[3].bits_per_pixel, &data->tab_texture[3].line_lenght, &data->tab_texture[3].endian); // WEST
//	data->texture.sprite = mlx_get_data_addr(data->texture.sprite,
//			&data->img.bits_per_pixel, &data->img.line_lenght, &data->img.endian); //
}

int direction_texture(t_data *data)
{
	if (data->ray.side == 0 && data->ray.ray_dirx < 0)
		data->texture.text_dir = 0;
	if (data->ray.side == 0 && data->ray.ray_dirx >= 0)
		data->texture.text_dir = 1;
	if (data->ray.side == 1 && data->ray.ray_dirx < 0)
		data->texture.text_dir = 2;
	if (data->ray.side == 1 && data->ray.ray_dirx >= 0)
		data->texture.text_dir = 3;
	if (data->ray.side == 0)
		data->texture.wallx = data->ray.pos_y + data->ray.perp_wall_dist * data->ray.ray_diry;
	else
		data->texture.wallx = data->ray.pos_x + data->ray.perp_wall_dist * data->ray.ray_dirx;
	printf("wallx = %d\n", data->texture.wallx);
	data->texture.wallx -= floor((data->texture.wallx));
	printf("wallx = %d\n", data->texture.wallx);
	return (0);
}

int draw_texture_walls(t_data *data, int pos_x)
{
	int y;

	y = data->ray.draw_start;
	data->tab_texture[0].height = 64;
	direction_texture(data);
	printf("height = %f\n", 1.0 * data->tab_texture[0].height);
	data->texture.step = 1.0 * data->tab_texture[0].height / data->ray.line_height;
	printf("wallx = %d\n(double)data->tab_texture[data->texture.text_dir].width = %f\n", data->texture.wallx, (double)data->tab_texture[data->texture.text_dir].width);
	data->texture.x = (int)(data->texture.wallx * (double)data->tab_texture[data->texture.text_dir].width);
	if (data->ray.side == 0 && data->ray.ray_dirx > 0)
		data->texture.x = data->tab_texture[data->texture.text_dir].width - data->texture.x - 1;
	if (data->ray.side == 1 && data->ray.ray_diry < 0)
		data->texture.x = data->tab_texture[data->texture.text_dir].width - data->texture.x - 1;
	data->texture.position = (data->ray.draw_start - data->param.resolution.axe_y / 2 + data->ray.line_height / 2) * data->texture.step;
	while (y <= data->ray.draw_end)
	{
		data->texture.y = (int)data->texture.position &
			(data->tab_texture[data->texture.text_dir].height - 1);
		data->texture.position += data->texture.step;
		printf("texture.x = %i\ntexture.y = %i\n", data->texture.x, data->texture.y);

		printf("data->tab_texture[data->texture.text_dir].addr[data->texture.y * data->tab_texture[data->texture.text_dir].line_lenght / 4 + data->texture.x] = %d\n", data->tab_texture[data->texture.text_dir].line_lenght / 4 + data->texture.x);
		exit (0);
		if (y < data->param.resolution.axe_y && pos_x < data->param.resolution.axe_x)
			data->img.addr[y * data->img.line_lenght / 4 + pos_x] = data->tab_texture[data->texture.text_dir].addr[data->texture.y * data->tab_texture[data->texture.text_dir].line_lenght / 4 + data->texture.x];
		y++;
	}
	return (0);
}
