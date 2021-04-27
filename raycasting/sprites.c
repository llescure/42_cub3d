#include "../include/struct_cub3d.h"
#include "../include/cub3d.h"

void	order_sprites(t_data *data)
{
	int		i;
	int		j;
	double	tmp;

	i = 0;
	while (i < data->param.nb_sprites)
	{
		j = 0;
		while (j < data->param.nb_sprites - 1)
		{
			if (data->tab_sprite[j].dist < data->tab_sprite[j + 1].dist)
			{
				tmp = data->tab_sprite[j].dist;
				data->tab_sprite[j].dist = data->tab_sprite[j + 1].dist;
				data->tab_sprite[j + 1].dist = tmp;
				tmp = data->tab_sprite[j].order;
				data->tab_sprite[j].order = data->tab_sprite[j + 1].order;
				data->tab_sprite[j].order = (int)tmp;
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
		data->tab_sprite[i].dist = ((data->ray.pos_x - data->tab_sprite[i].sprite_y *
					(data->ray.pos_x - data->tab_sprite[i].sprite_y) + (data->ray.pos_y
						- data->tab_sprite[i].sprite_x) * (data->ray.pos_y -
							data->tab_sprite[i].sprite_x)));
		i++;
	}
	order_sprites(data);
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

	i = sprite->draw_start_y;
	text_y = 0;
	while (i < sprite->draw_end_y)
	{
		img_cord = 4 * stripe + 4 * data->param.resolution.axe_x * i;
		sprite_cord = 4 * text_y * 64 + 4 * text_x;
		d = i * 256 - data->param.resolution.axe_y * 128 + sprite->height
			* 128;
		text_y = ((d * 64) / 64) / 256;
		if (sprite->img.addr[sprite_cord])
			data->img.addr[img_cord] = sprite->img.addr[sprite_cord];
		if (sprite->img.addr[sprite_cord + 1])
			data->img.addr[img_cord + 1] =
				sprite->img.addr[sprite_cord + 1];
		if (sprite->img.addr[sprite_cord + 2])
			data->img.addr[img_cord + 2] =
				sprite->img.addr[sprite_cord + 2];
		if (sprite->img.addr[sprite_cord + 3])
			data->img.addr[img_cord + 3] =
				sprite->img.addr[sprite_cord + 3];
		i++;
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
							data->tab_sprite[i].screen)) * 64 /
					data->tab_sprite[i].width) / 256;
			if (data->tab_sprite[i].transform_y > 0 && stripe > 0 && stripe <
					data->param.resolution.axe_x && data->tab_sprite[i].transform_y <
					data->tab_sprite[i].z_buffer[stripe])
				draw_sprites(data, stripe, text_x, &data->tab_sprite[i]);
		}
	}
}
