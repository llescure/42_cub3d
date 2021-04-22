#include "../include/struct_cub3d.h"
#include "../include/cub3d.h"

void	order_sprites_1(t_data *data)
{
	int		i;
	int		j;
	double	tmp;

	i = 0;
	while (i < data->param.nb_sprite_1)
	{
		j = 0;
		while (j < data->param.nb_sprite_1 - 1)
		{
			if (data->sprite.dist[j] < data->sprite.dist[j + 1])
			{
				tmp = data->sprite.dist[j];
				data->sprite.dist[j] = data->sprite.dist[j + 1];
				data->sprite.dist[j + 1] = tmp;
				tmp = data->sprite.order[j];
				data->sprite.order[j] = data->sprite.order[j + 1];
				data->sprite.order[j + 1] = (int)tmp;
			}
			j++;
		}
		i++;
	}
}

void	sort_sprites(t_data *data)
{
	int i;

	i = 0;
	while (i < data->param.nb_sprite_1)
	{
		data->sprite.order[i] = i;
		data->sprite.dist[i] = ((data->ray.pos_x - data->sprite.sprite_y[i]) *
				(data->ray.pos_x - data->sprite.sprite_y[i]) + (data->ray.pos_y
					- data->sprite.sprite_x[i]) * (data->ray.pos_y -
						data->sprite.sprite_x[i]));
		i++;
	}
	i = 0;
	while (i < data->param.nb_sprite_2)
	{
		data->sprite2.order[i] = i;
		data->sprite2.dist[i] = ((data->ray.pos_x - data->sprite2.sprite_y[i]) *
				(data->ray.pos_x - data->sprite2.sprite_y[i]) + (data->ray.pos_y
					- data->sprite2.sprite_x[i]) * (data->ray.pos_y -
						data->sprite2.sprite_x[i]));
		i++;
	}
	order_sprites_1(data);
	order_sprites_2(data);
}

void	calculate_sprites_1(t_data *data, int i)
{
	initialize_data_for_sprites_1(data, i);
	if (data->sprite.draw_start_y < 0)
		data->sprite.draw_start_y = 0;
	data->sprite.draw_end_y = data->sprite.height / 2 +
		data->param.resolution.axe_y / 2;
	if (data->sprite.draw_end_y >= data->param.resolution.axe_y)
		data->sprite.draw_end_y = data->param.resolution.axe_y - 1;
	data->sprite.width = abs((int)(data->param.resolution.axe_y /
				data->sprite.transform_y));
	data->sprite.draw_start_x = -data->sprite.width / 2 + data->sprite.screen;
	if (data->sprite.draw_start_x < 0)
		data->sprite.draw_start_x = 0;
	data->sprite.draw_end_x = data->sprite.width / 2 + data->sprite.screen;
	if (data->sprite.draw_end_x >= data->param.resolution.axe_x)
		data->sprite.draw_end_x = data->param.resolution.axe_x - 1;
}

void	draw_sprites_1(t_data *data, int stripe, int text_x, int text_y)
{
	int i;
	int d;
	int img_cord;
	int sprite_cord;

	i = data->sprite.draw_start_y - 1;
	while (++i < data->sprite.draw_end_y)
	{
		img_cord = 4 * stripe + 4 * data->param.resolution.axe_x * i;
		sprite_cord = 4 * text_y * data->sprite.img.height + 4 * text_x;
		d = i * 256 - data->param.resolution.axe_y * 128 + data->sprite.height
			* 128;
		text_y = ((d * data->sprite.img.height) / data->sprite.height) / 256;
		if (data->sprite.img.addr[sprite_cord]) // si c'est transparent
			data->img.addr[img_cord] = data->sprite.img.addr[sprite_cord];
		if (data->sprite.img.addr[sprite_cord + 1]) // si c'est rouge
			data->img.addr[img_cord + 1] =
				data->sprite.img.addr[sprite_cord + 1];
		if (data->sprite.img.addr[sprite_cord + 2]) // si c'est vert
			data->img.addr[img_cord + 2] =
				data->sprite.img.addr[sprite_cord + 2];
		if (data->sprite.img.addr[sprite_cord + 3]) // si c'est bleu
			data->img.addr[img_cord + 3] =
				data->sprite.img.addr[sprite_cord + 3];
	}
}

void	ft_sprites(t_data *data)
{
	int	i;
	int	stripe;
	int	text_x;

	i = -1;
	sort_sprites(data);
	while (++i < data->param.nb_sprite_1)
	{
		calculate_sprites_1(data, i);
		stripe = data->sprite.draw_start_x - 1;
		while (++stripe < data->sprite.draw_end_x)
		{
			text_x = (int)(256 * (stripe - (-data->sprite.width / 2 +
							data->sprite.screen)) * data->sprite.img.width /
					data->sprite.width) / 256;
			if (data->sprite.transform_y > 0 && stripe > 0 && stripe <
					data->param.resolution.axe_x && data->sprite.transform_y <
					data->sprite.z_buffer[stripe])
				draw_sprites_1(data, stripe, text_x, 0);
		}
	}
	i = -1;
	while (++i < data->param.nb_sprite_2)
	{
		calculate_sprites_2(data, i);
		stripe = data->sprite2.draw_start_x - 1;
		while (++stripe < data->sprite2.draw_end_x)
		{
			text_x = (int)(256 * (stripe - (-data->sprite2.width / 2 +
							data->sprite2.screen)) * data->sprite2.img.width /
					data->sprite2.width) / 256;
			if (data->sprite2.transform_y > 0 && stripe > 0 && stripe <
					data->param.resolution.axe_x && data->sprite2.transform_y <
					data->sprite.z_buffer[stripe])
				draw_sprites_2(data, stripe, text_x, 0);
		}
	}
}
