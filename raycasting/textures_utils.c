#include "../include/struct_cub3d.h"
#include "../include/cub3d.h"

void	initialize_before_drawing(t_data *data)
{
	direction_texture(data);
	data->texture.step = 1.0 * data->tab_texture[data->texture.text_dir].height
		/ data->ray.line_height;
	data->texture.x = (int)(data->texture.wallx *
			(double)data->tab_texture[data->texture.text_dir].width);
	data->texture.position = (data->ray.draw_start - data->param.resolution.
			axe_y / 2 + data->ray.line_height / 2) * data->texture.step;
}

void	free_textures(t_data *data)
{
	int	i;

	i = 0;
	while (i <= 3)
	{
		if (data->tab_texture[i].img)
			mlx_destroy_image(data->mlx_ptr, data->tab_texture[i].img);
		if (data->bonus.tab_life[i].img)
			mlx_destroy_image(data->mlx_ptr, data->bonus.tab_life[i].img);
		i++;
	}
	while (i < 4)
	{
		if (data->tab_texture[i].img)
			mlx_destroy_image(data->mlx_ptr, data->tab_texture[i].img);
		i++;
	}
	free_sprites(data);
	free_textures_bonus(data);
}

void	free_sprites(t_data *data)
{
	int i;

	i = 0;
	while (i < data->param.nb_sprites)
	{
		free(data->tab_sprite[i].z_buffer);
		i++;
	}
	if (data->tab_sprite)
		free(data->tab_sprite);
	if (data->sprite1.img)
		mlx_destroy_image(data->mlx_ptr, data->sprite1.img);
	if (data->sprite2.img)
		mlx_destroy_image(data->mlx_ptr, data->sprite2.img);
}

void	get_sprites2_img(t_data *data)
{
	if (!(data->sprite2.img = mlx_xpm_file_to_image(data->mlx_ptr,
					data->param.sprite_2, &(data->sprite2.width),
					&(data->sprite2.height))))
		print_error_2(&data->param, "Error with texture");
	data->sprite2.addr = mlx_get_data_addr(data->sprite2.img,
			&data->sprite2.bits_per_pixel,
			&data->sprite2.line_lenght,
			&data->sprite2.endian);
}
