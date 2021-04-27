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
//	free_sprites(data);
	free_textures_bonus(data);
}
