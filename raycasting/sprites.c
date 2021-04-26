#include "../include/struct_cub3d.h"
#include "../include/cub3d.h"

void	order_sprites(t_data *data)
{
	int		i;
	int		j;
	double	tmp;
	char	*tmp2;

	i = 0;
	while (i < data->param.nb_sprites)
	{
		j = 0;
		while (j < data->param.nb_sprites - 1)
		{
			if (data->sprite.dist[j] < data->sprite.dist[j + 1])
			{
				tmp = data->sprite.dist[j];
				data->sprite.dist[j] = data->sprite.dist[j + 1];
				data->sprite.dist[j + 1] = tmp;
				tmp = data->sprite.order[j];
				data->sprite.order[j] = data->sprite.order[j + 1];
				data->sprite.order[j + 1] = (int)tmp;
				tmp2 = data->tab_sprite[i + 1].img.addr;
				data->tab_sprite[i + 1].img.addr = data->tab_sprite[i].img.addr;
				data->tab_sprite[i].img.addr = tmp2;
				j = -1;
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
		data->sprite.order[i] = i;
		data->sprite.dist[i] = ((data->ray.pos_x - data->tab_sprite[i].sprite_y *
				(data->ray.pos_x - data->tab_sprite[i].sprite_y) + (data->ray.pos_y
					- data->tab_sprite[i].sprite_x) * (data->ray.pos_y -
						data->tab_sprite[i].sprite_x)));
		i++;
	}
	order_sprites(data);
}

void	calculate_sprites(t_data *data, int i, t_sprite *sprite)
{
	initialize_data_for_sprites(data, i);
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

void	draw_sprites(t_data *data, int stripe, int text_x, int text_y, int k)
{
	int i;
	int d;
	int img_cord;
	int sprite_cord;

	i = data->sprite.draw_start_y - 1;
	while (++i < data->sprite.draw_end_y)
	{
		img_cord = 4 * stripe + 4 * data->param.resolution.axe_x * i;
		sprite_cord = 4 * text_y * 64 + 4 * text_x;
		d = i * 256 - data->param.resolution.axe_y * 128 + data->sprite.height
			* 128;
		text_y = ((d * 64) / 64) / 256;
		if (data->tab_sprite[k].img.addr[sprite_cord])
			data->img.addr[img_cord] = data->sprite.img.addr[sprite_cord];
		if (data->tab_sprite[k].img.addr[sprite_cord + 1])
			data->img.addr[img_cord + 1] =
				data->tab_sprite[k].img.addr[sprite_cord + 1];
		if (data->tab_sprite[k].img.addr[sprite_cord + 2])
			data->img.addr[img_cord + 2] =
				data->tab_sprite[k].img.addr[sprite_cord + 2];
		if (data->tab_sprite[k].img.addr[sprite_cord + 3])
			data->img.addr[img_cord + 3] =
				data->tab_sprite[k].img.addr[sprite_cord + 3];
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
		calculate_sprites(data, i, &data->sprite);
		stripe = data->sprite.draw_start_x - 1;
		while (++stripe < data->sprite.draw_end_x)
		{
			text_x = (int)(256 * (stripe - (-data->sprite.width / 2 +
							data->sprite.screen)) * 64 /
					data->sprite.width) / 256;
			if (data->sprite.transform_y > 0 && stripe > 0 && stripe <
					data->param.resolution.axe_x && data->sprite.transform_y <
					data->sprite.z_buffer[stripe])
				draw_sprites(data, stripe, text_x, 0, i);
		}
	}
}
