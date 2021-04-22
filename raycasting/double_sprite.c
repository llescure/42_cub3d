#include "../include/struct_cub3d.h"
#include "../include/cub3d.h"

void	order_sprites_2(t_data *data)
{
	int i;
	int j;
	double tmp;

	i = 0;
	while (i < data->param.nb_sprite_2)
	{
		j = 0;
		while (j < data->param.nb_sprite_2 - 1)
		{
			if (data->sprite2.dist[j] < data->sprite2.dist[j + 1])
			{
				tmp = data->sprite2.dist[j];
				data->sprite2.dist[j] = data->sprite2.dist[j + 1];
				data->sprite2.dist[j + 1] = tmp;
				tmp = data->sprite2.order[j];
				data->sprite2.order[j] = data->sprite2.order[j + 1];
				data->sprite2.order[j + 1] = (int)tmp;
			}
			j++;
		}
		i++;
	}
}

void	calculate_sprites_2(t_data *data, int i)
{
	initialize_data_for_sprites_2(data, i);
	if (data->sprite2.draw_start_y < 0)
		data->sprite2.draw_start_y = 0;
	data->sprite2.draw_end_y = data->sprite2.height / 2 +
		data->param.resolution.axe_y / 2;
	if (data->sprite2.draw_end_y >= data->param.resolution.axe_y)
		data->sprite2.draw_end_y = data->param.resolution.axe_y - 1;
	data->sprite2.width = abs((int)(data->param.resolution.axe_y /
				data->sprite2.transform_y));
	data->sprite2.draw_start_x = -data->sprite2.width / 2 + data->sprite2.screen;
	if (data->sprite2.draw_start_x < 0)
		data->sprite2.draw_start_x = 0;
	data->sprite2.draw_end_x = data->sprite2.width / 2 + data->sprite2.screen;
	if (data->sprite2.draw_end_x >= data->param.resolution.axe_x)
		data->sprite2.draw_end_x = data->param.resolution.axe_x - 1;
}

void	draw_sprites_2(t_data *data, int stripe, int text_x, int text_y)
{
	int i;
	int d;
	int img_cord;
	int sprite_cord;

	i = data->sprite2.draw_start_y - 1;
	while (++i < data->sprite2.draw_end_y)
	{
		img_cord = 4 * stripe + 4 * data->param.resolution.axe_x * i;
		sprite_cord = 4 * text_y * data->sprite2.img.height + 4 * text_x;
		d = i * 256 - data->param.resolution.axe_y * 128 + data->sprite2.height
			* 128;
		text_y = ((d * data->sprite2.img.height) / data->sprite2.height) / 256;
		if (data->sprite2.img.addr[sprite_cord]) // si c'est transparent
			data->img.addr[img_cord] = data->sprite2.img.addr[sprite_cord];
		if (data->sprite2.img.addr[sprite_cord + 1]) // si c'est rouge
			data->img.addr[img_cord + 1] =
				data->sprite2.img.addr[sprite_cord + 1];
		if (data->sprite2.img.addr[sprite_cord + 2]) // si c'est vert
			data->img.addr[img_cord + 2] =
				data->sprite2.img.addr[sprite_cord + 2];
		if (data->sprite2.img.addr[sprite_cord + 3]) // si c'est bleu
			data->img.addr[img_cord + 3] =
				data->sprite2.img.addr[sprite_cord + 3];
	}
}

void	free_sprites(t_data *data)
{
	if (data->sprite.img.img)
		mlx_destroy_image(data->mlx_ptr, data->sprite.img.img);
	if (data->sprite2.img.img)
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
}
