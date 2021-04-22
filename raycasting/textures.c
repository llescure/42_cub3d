#include "../include/struct_cub3d.h"
#include "../include/cub3d.h"

int ft_get_addr_textures(t_data *data)
{
	if (!(data->tab_texture[0].img = mlx_xpm_file_to_image(data->mlx_ptr,
					data->param.north_texture, &(data->tab_texture[0].width),
					&(data->tab_texture[0].height))))
		exit (0);
	if (!(data->tab_texture[1].img = mlx_xpm_file_to_image(data->mlx_ptr,
					data->param.south_texture, &(data->tab_texture[1].width),
					&(data->tab_texture[1].height))))
		exit (0);
	if (!(data->tab_texture[2].img = mlx_xpm_file_to_image(data->mlx_ptr,
					data->param.east_texture, &(data->tab_texture[2].width),
					&(data->tab_texture[2].height))))
		exit (0);
	if (!(data->tab_texture[3].img = mlx_xpm_file_to_image(data->mlx_ptr,
					data->param.west_texture, &(data->tab_texture[3].width),
					&(data->tab_texture[3].height))))
		exit (0);
	if (!(data->sprite.img.img = mlx_xpm_file_to_image(data->mlx_ptr,
					data->param.sprite_1, &(data->sprite.img.width),
					&(data->sprite.img.height))))
		exit (0);
	if (!(data->sprite2.img.img = mlx_xpm_file_to_image(data->mlx_ptr,
					data->param.sprite_2, &(data->sprite2.img.width),
					&(data->sprite2.img.height))))
		exit (0);
	return (0);
}

void get_textures(t_data *data)
{
	ft_get_addr_textures(data);
	data->tab_texture[0].addr = mlx_get_data_addr(data->tab_texture[0].img,
			&data->tab_texture[0].bits_per_pixel, &data->tab_texture[0].
			line_lenght, &data->tab_texture[0].endian); // NORTH
	data->tab_texture[1].addr = mlx_get_data_addr(data->tab_texture[1].img,
			&data->tab_texture[1].bits_per_pixel, &data->tab_texture[1].
			line_lenght, &data->tab_texture[1].endian); // SOUTH
	data->tab_texture[2].addr = mlx_get_data_addr(data->tab_texture[2].img,
			&data->tab_texture[2].bits_per_pixel, &data->tab_texture[2].
			line_lenght, &data->tab_texture[2].endian);	// EAST
	data->tab_texture[3].addr = mlx_get_data_addr(data->tab_texture[3].img,
			&data->tab_texture[3].bits_per_pixel,
			&data->tab_texture[3].line_lenght, &data->tab_texture[3].endian); // WEST
	data->sprite.img.addr = mlx_get_data_addr(data->sprite.img.img,
			&data->sprite.img.bits_per_pixel, &data->sprite.img.line_lenght,
			&data->sprite.img.endian); // SPRITE

	data->sprite2.img.addr = mlx_get_data_addr(data->sprite2.img.img,
			&data->sprite2.img.bits_per_pixel, &data->sprite2.img.line_lenght,
			&data->sprite2.img.endian); // SPRITE
}

int direction_texture(t_data *data)
{
	if (data->ray.side == 0 && data->ray.ray_diry < 0)
		data->texture.text_dir = 0;
	if (data->ray.side == 0 && data->ray.ray_diry >= 0)
		data->texture.text_dir = 1;
	if (data->ray.side == 1 && data->ray.ray_diry < 0)
		data->texture.text_dir = 2;
	if (data->ray.side == 1 && data->ray.ray_diry >= 0)
		data->texture.text_dir = 3;
	if (data->ray.side == 0)
		data->texture.wallx = data->ray.pos_y + data->ray.perp_wall_dist *
			data->ray.ray_diry;
	else
		data->texture.wallx = data->ray.pos_x + data->ray.perp_wall_dist *
			data->ray.ray_dirx;
	data->texture.wallx -= floor((data->texture.wallx));
	return (0);
}

int draw_texture_walls(t_data *data, int pos_x)
{
	int y;

	y = data->ray.draw_start;
	direction_texture(data);
	data->texture.step = 1.0 * data->tab_texture[data->texture.text_dir].height
		/ data->ray.line_height;
	data->texture.x = (int)(data->texture.wallx *
			(double)data->tab_texture[data->texture.text_dir].width);
	data->texture.position = (data->ray.draw_start - data->param.resolution.
			axe_y / 2 + data->ray.line_height / 2) * data->texture.step;
	while (y < data->ray.draw_end)
	{
		data->texture.y = (int)data->texture.position &
			(data->tab_texture[data->texture.text_dir].height - 1);
		data->texture.position += data->texture.step;
		data->img.addr[pos_x * 4 + 4 * data->param.resolution.axe_x * y] =
			data->tab_texture[data->texture.text_dir].addr[data->texture.y *
			data->tab_texture[data->texture.text_dir].height * 4 +
			data->texture.x * 4] * data->texture.shade;
		data->img.addr[pos_x * 4 + 4 * data->param.resolution.axe_x * y + 1] =
			data->tab_texture[data->texture.text_dir].addr[data->texture.y *
			data->tab_texture[data->texture.text_dir].height * 4 +
			data->texture.x * 4 + 1] * data->texture.shade;
		data->img.addr[pos_x * 4 + 4 * data->param.resolution.axe_x * y + 2] =
			data->tab_texture[data->texture.text_dir].addr[data->texture.y *
			data->tab_texture[data->texture.text_dir].height * 4 +
			data->texture.x * 4 + 2] * data->texture.shade;
		data->img.addr[pos_x * 4 + 4 * data->param.resolution.axe_x * y + 3] =
			data->tab_texture[data->texture.text_dir].addr[data->texture.y *
			data->tab_texture[data->texture.text_dir].height * 4 +
			data->texture.x * 4 + 3] * data->texture.shade;
		y++;
	}
	return (0);
}

void	free_textures(t_data *data)
{
	int	i;

	i = 0;
	while (i < 3)
	{
		if (data->tab_texture[i].img)
			mlx_destroy_image(data->mlx_ptr, data->tab_texture[i].img);
		if (data->bonus.tab_life[i].img)
			mlx_destroy_image(data->mlx_ptr, data->bonus.tab_life[i].img);
		i++;
	}
	if (data->tab_texture[i].img)
		mlx_destroy_image(data->mlx_ptr, data->tab_texture[i].img);
	free_sprites(data);
}
