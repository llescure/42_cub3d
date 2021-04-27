#include "../include/struct_cub3d.h"
#include "../include/cub3d.h"

void	order_sprites(t_data *data, int nb_sprites)
{
	int		i;
	int		j;
	t_sprite	tmp;

	i = 0;
	while (i < nb_sprites)
	{
		j = i + 1;
		while (j < nb_sprites)
		{
			if (data->tab_sprite[i].dist < data->tab_sprite[j].dist)
			{
				tmp = data->tab_sprite[i];
				data->tab_sprite[i] = data->tab_sprite[j];
				data->tab_sprite[j] = tmp;
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
	while (i < data->param.nb_sprites)
	{
		data->tab_sprite[i].order = i;
		data->tab_sprite[i].dist = ((data->ray.pos_x - data->tab_sprite[i].sprite_y) *
			(data->ray.pos_x - data->tab_sprite[i].sprite_y) + (data->ray.pos_y
			- data->tab_sprite[i].sprite_x) * (data->ray.pos_y -
			data->tab_sprite[i].sprite_x));
		i++;
	}
	order_sprites(data, data->param.nb_sprites);
}

void	calculate_sprites(t_data *data, t_sprite *sprite)
{
	initialize_data_for_sprites(data, sprite);
	if (sprite->draw_start_y < 0)
		sprite->draw_start_y = 0;
	sprite->draw_end_y = sprite->height / 2 + data->param.resolution.axe_y / 2;
	if (sprite->draw_end_y >= data->param.resolution.axe_y)
		sprite->draw_end_y = data->param.resolution.axe_y - 1;
	sprite->width = abs((int)(data->param.resolution.axe_y / sprite->transform_y));
	sprite->draw_start_x = -sprite->width / 2 + sprite->screen;
	if (sprite->draw_start_x < 0)
		sprite->draw_start_x = 0;
	sprite->draw_end_x = sprite->width / 2 + sprite->screen;
	if (sprite->draw_end_x >= data->param.resolution.axe_x)
		sprite->draw_end_x = data->param.resolution.axe_x - 1;
}

void	draw_sprites(t_data *data, int stripe, int text_x, t_sprite *sprite)
{
	int i;
	int d;
	int img_cord;
	int sprite_cord;
	int text_y;

	text_y = 0;
	i = sprite->draw_start_y - 1;
	while (++i < sprite->draw_end_y)
	{
		d = i * 256 - data->param.resolution.axe_y * 128 + sprite->height
			* 128;
		text_y = ((d * sprite->img.height) / sprite->height) / 256;
		img_cord = 4 * stripe + 4 * data->param.resolution.axe_x * i;
		sprite_cord = 4 * text_y * sprite->img.height + 4 * text_x;
		if (sprite->img.addr[sprite_cord])
			data->img.addr[img_cord] = sprite->img.addr[sprite_cord] / data->texture.shade;
		if (sprite->img.addr[sprite_cord + 1])
			data->img.addr[img_cord + 1] =
				sprite->img.addr[sprite_cord + 1] / data->texture.shade;
		if (sprite->img.addr[sprite_cord + 2])
			data->img.addr[img_cord + 2] =
				sprite->img.addr[sprite_cord + 2] / data->texture.shade;
		if (sprite->img.addr[sprite_cord + 3])
			data->img.addr[img_cord + 3] =
				sprite->img.addr[sprite_cord + 3] / data->texture.shade;
	}
}

void	ft_sprites(t_data *data)
{
	int	i;
	int	stripe;
	int	text_x;

	i = -1;
	sort_sprites(data);
	while (++i < data->param.nb_sprites)
	{
		calculate_sprites(data, &data->tab_sprite[i]);
		stripe = data->tab_sprite[i].draw_start_x - 1;
		while (++stripe < data->tab_sprite[i].draw_end_x)
		{
			text_x = (int)(256 * (stripe - (-data->tab_sprite[i].width / 2 +
				data->tab_sprite[i].screen)) * data->tab_sprite[i].img.width /
					data->tab_sprite[i].width) / 256;
			if (data->tab_sprite[i].transform_y > 0 && stripe > 0 && stripe <
					data->param.resolution.axe_x && data->tab_sprite[i].transform_y <
					data->tab_sprite[i].z_buffer[stripe])
			{
				get_image_by_sprite(data, &data->tab_sprite[i]);
				draw_sprites(data, stripe, text_x, &data->tab_sprite[i]);
			}
		}
	}
}
