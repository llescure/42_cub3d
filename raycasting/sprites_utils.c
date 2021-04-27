#include "../include/struct_cub3d.h"
#include "../include/cub3d.h"

void	allocate_memory_for_sprites(t_data *data)
{
	if (!(data->tab_sprite = malloc(sizeof(t_sprite) *
					data->param.nb_sprites))) 
		print_error(&data->param, "sprites failed");
}

void	get_sprites_info(t_data *data)
{
	int i;
	int j;
	int k;

	allocate_memory_for_sprites(data);
	k = 0;
	i = 0;
	while (i < data->param.map.nb_lines)
	{
		j = 0;
		while (j < data->param.map.max_length)
		{
			if (data->param.map.tab_map[i][j] == '2')
			{
				data->tab_sprite[k].sprite_y = (double)i + 0.5;
				data->tab_sprite[k].sprite_x = (double)j + 0.5;
				data->tab_sprite[k].type = '2';
				k++;
			}
			else if (data->param.map.tab_map[i][j] == '3')
			{
				data->tab_sprite[k].sprite_y = (double)i + 0.5;
				data->tab_sprite[k].sprite_x = (double)j + 0.5;
				data->tab_sprite[k].type = '3';
				k++;
			}
			j++;
		}
		i++;
	}
}

void	get_image_by_sprite(t_data *data, t_sprite *sprite)
{
	if (sprite->type == '2')
	{
		sprite->img.img = mlx_xpm_file_to_image(data->mlx_ptr,
		data->param.sprite_1, &(sprite->img.width),
		&(sprite->img.height));
		sprite->img.addr = mlx_get_data_addr(sprite->img.img,
		&sprite->img.bits_per_pixel, &sprite->img.line_lenght,
		&sprite->img.endian);
	}
	else if (sprite->type == '3')
	{
		sprite->img.img = mlx_xpm_file_to_image(data->mlx_ptr,
		data->param.sprite_2, &(sprite->img.width),
		&(sprite->img.height));
		sprite->img.addr = mlx_get_data_addr(sprite->img.img,
		&sprite->img.bits_per_pixel, &sprite->img.line_lenght,
		&sprite->img.endian);
	}
}

void	initialize_data_for_sprites(t_data *data, t_sprite *sprite)
{
	sprite->pos_x = sprite->sprite_x - data->ray.pos_y;
	sprite->pos_y = sprite->sprite_y - data->ray.pos_x;
	sprite->invdet = 1.0 / (data->ray.plan_x * data->ray.dir_y - data->ray.dir_x *
			data->ray.plan_y);
	sprite->transform_x = sprite->invdet * (data->ray.dir_y * sprite->pos_x -
			data->ray.dir_x * sprite->pos_y);
	sprite->transform_y = sprite->invdet * (-data->ray.plan_y * sprite->pos_x +
			data->ray.plan_x * sprite->pos_y);
	sprite->screen = (int)((data->param.resolution.axe_x / 2) * (1 +
				sprite->transform_x / sprite->transform_y));
	sprite->height = abs((int)(data->param.resolution.axe_y / sprite->transform_y));
	sprite->draw_start_y = -sprite->height / 2 +
		data->param.resolution.axe_y / 2;
}

/*void	free_sprites(t_data *data)
{
	if (data->sprite.img.img)
		mlx_destroy_image(data->mlx_ptr, data->sprite.img.img);
	if (data->param.bonus == '1' && data->sprite2.img.img)
		mlx_destroy_image(data->mlx_ptr, data->sprite2.img.img);
	if (data->sprite.z_buffer)
		free(data->sprite.z_buffer);
	if (data->sprite.sprite_x)
		free(data->sprite.sprite_x);
	if (data->sprite.sprite_y)
		free(data->sprite.sprite_y);
	if (data->sprite.order)
		free(data->sprite.order);
	if (data->sprite.dist)
		free(data->sprite.dist);
	if (data->sprite2.sprite_x)
		free(data->sprite2.sprite_x);
	if (data->sprite2.sprite_y)
		free(data->sprite2.sprite_y);
	if (data->sprite2.order)
		free(data->sprite2.order);
	if (data->sprite2.dist)
		free(data->sprite2.dist);
}*/
