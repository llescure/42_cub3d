#include "../include/struct_cub3d.h"
#include "../include/cub3d.h"

void	allocate_memory_for_sprites(t_data *data)
{
	int i;

	i = 0;
	if (!(data->tab_sprite = malloc(sizeof(t_sprite) *
		data->param.nb_sprites)))
		print_error_2(&data->param, "sprites failed");
	while (i < data->param.nb_sprites)
	{
		set_data(&data->tab_sprite[i]);
		i++;
	}
}

void	set_data(t_sprite *sprite)
{
	sprite->sprite_x = 0;
	sprite->sprite_y = 0;
	sprite->draw_start_x = 0;
	sprite->draw_start_y = 0;
	sprite->draw_end_x = 0;
	sprite->draw_end_y = 0;
	sprite->pos_x = 0;
	sprite->pos_y = 0;
	sprite->height = 0;
	sprite->width = 0;
	sprite->transform_x = 0;
	sprite->transform_y = 0;
	sprite->dist = 0;
	sprite->screen = 0;
	sprite->order = 0;
	sprite->invdet = 0;
	sprite->type = '0';
	sprite->img.img = NULL;
	sprite->img.addr = NULL;
	sprite->img.bits_per_pixel = 0;
	sprite->img.line_length = 0;
	sprite->img.endian = 0;
	sprite->img.width = 0;
	sprite->img.height = 0;
}

void	get_sprites_info(t_data *data)
{
	int i;
	int j;
	int k;

	k = 0;
	i = 0;
	allocate_memory_for_sprites(data);
	while (i < data->param.map.nb_lines)
	{
		j = 0;
		while (j < data->param.map.max_length)
		{
			if (data->param.map.tab_map[i][j] == '2')
				k += initialize_sprite(i, j, &data->tab_sprite[k], '2');
			else if (data->param.map.tab_map[i][j] == '3')
				k += initialize_sprite(i, j, &data->tab_sprite[k], '3');
			j++;
		}
		i++;
	}
}

int		initialize_sprite(int i, int j, t_sprite *sprite, char type)
{
	sprite->sprite_y = (double)i + 0.5;
	sprite->sprite_x = (double)j + 0.5;
	sprite->type = type;
	return (1);
}
