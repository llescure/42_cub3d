#include "../include/struct_cub3d.h"
#include "../include/cub3d.h"

void	allocate_memory_for_sprites(t_data *data)
{
	if (!(data->sprite.sprite_x = (double *)malloc(sizeof(double) *
					data->param.nb_sprite_1)) || !(data->sprite.sprite_y =
					(double *)malloc(sizeof(double) * data->param.nb_sprite_1))
			|| !(data->sprite.order = (int *)malloc(sizeof(int) *
					data->param.nb_sprite_1)) || !(data->sprite.dist =
					(double *)malloc(sizeof(double) * data->param.nb_sprite_1)))
		print_error(&data->param, "sprites failed");
	if (!(data->sprite2.sprite_x = (double *)malloc(sizeof(double) *
					data->param.nb_sprite_2)) || !(data->sprite2.sprite_y =
					(double *)malloc(sizeof(double) * data->param.nb_sprite_2))
			|| !(data->sprite2.order = (int *)malloc(sizeof(int) *
					data->param.nb_sprite_2)) || !(data->sprite2.dist =
					(double *)malloc(sizeof(double) * data->param.nb_sprite_2)))
		print_error(&data->param, "sprites failed");

}


void	get_sprites_info(t_data *data)
{
	int i;
	int j;
	int k;
	int l;

	allocate_memory_for_sprites(data);
	k = 0;
	i = 0;
	l = 0;
	while (i < data->param.map.nb_lines)
	{
		j = 0;
		while (data->param.map.tab_map[i][j] != '\0')
		{
			if (data->param.map.tab_map[i][j] == '2')
			{
				data->sprite.sprite_y[k] = (double)i + 0.5;
				data->sprite.sprite_x[k] = (double)j + 0.5;
				k++;
			}
			if (data->param.map.tab_map[i][j] == '3')
			{
				data->sprite2.sprite_y[l] = (double)i + 0.5;
				data->sprite2.sprite_x[l] = (double)j + 0.5;
				l++;
			}
			j++;
		}
		i++;
	}
}

void	initialize_data_for_sprites_1(t_data *data, int i)
{
	data->sprite.pos_x = data->sprite.sprite_x[data->sprite.order[i]] -
		data->ray.pos_y;
	data->sprite.pos_y = data->sprite.sprite_y[data->sprite.order[i]] -
		data->ray.pos_x;
	data->sprite.invdet = 1.0 / (data->ray.plan_x * data->ray.dir_y -
			data->ray.dir_x * data->ray.plan_y);
	data->sprite.transform_x = data->sprite.invdet * (data->ray.dir_y *
			data->sprite.pos_x - data->ray.dir_x * data->sprite.pos_y);
	data->sprite.transform_y = data->sprite.invdet * (-data->ray.plan_y *
			data->sprite.pos_x + data->ray.plan_x * data->sprite.pos_y);
	data->sprite.screen = (int)((data->param.resolution.axe_x / 2) * (1 +
				data->sprite.transform_x / data->sprite.transform_y));
	data->sprite.height = abs((int)(data->param.resolution.axe_y /
				data->sprite.transform_y));
	data->sprite.draw_start_y = -data->sprite.height / 2 +
		data->param.resolution.axe_y / 2;
}

void	initialize_data_for_sprites_2(t_data *data, int i)
{
	data->sprite2.pos_x = data->sprite2.sprite_x[data->sprite2.order[i]] -
		data->ray.pos_y;
	data->sprite2.pos_y = data->sprite2.sprite_y[data->sprite2.order[i]] -
		data->ray.pos_x;
	data->sprite2.invdet = 1.0 / (data->ray.plan_x * data->ray.dir_y -
			data->ray.dir_x * data->ray.plan_y);
	data->sprite2.transform_x = data->sprite2.invdet * (data->ray.dir_y *
			data->sprite2.pos_x - data->ray.dir_x * data->sprite2.pos_y);
	data->sprite2.transform_y = data->sprite2.invdet * (-data->ray.plan_y *
			data->sprite2.pos_x + data->ray.plan_x * data->sprite2.pos_y);
	data->sprite2.screen = (int)((data->param.resolution.axe_x / 2) * (1 +
				data->sprite2.transform_x / data->sprite2.transform_y));
	data->sprite2.height = abs((int)(data->param.resolution.axe_y /
				data->sprite2.transform_y));
	data->sprite2.draw_start_y = -data->sprite2.height / 2 +
		data->param.resolution.axe_y / 2;
}
