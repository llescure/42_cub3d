#include "../include/struct_cub3d.h"
#include "../include/cub3d.h"

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
		if (data->sprite2.img.addr[sprite_cord])
			data->img.addr[img_cord] = data->sprite2.img.addr[sprite_cord];
		if (data->sprite2.img.addr[sprite_cord + 1])
			data->img.addr[img_cord + 1] =
				data->sprite2.img.addr[sprite_cord + 1];
		if (data->sprite2.img.addr[sprite_cord + 2])
			data->img.addr[img_cord + 2] =
				data->sprite2.img.addr[sprite_cord + 2];
		if (data->sprite2.img.addr[sprite_cord + 3])
			data->img.addr[img_cord + 3] =
				data->sprite2.img.addr[sprite_cord + 3];
	}
}

void	check_sprite2(char *str, t_param *param)
{
	param->bonus = '1';
	param->sprite_2 = save_address_param(str, param);
}
