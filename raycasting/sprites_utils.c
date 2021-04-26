#include "../include/struct_cub3d.h"
#include "../include/cub3d.h"

void	allocate_memory_for_sprites(t_data *data)
{
	if (!(data->tab_sprite = (t_sprite *)malloc(sizeof(t_sprite) *
					data->param.nb_sprites + 1))
			|| !(data->sprite.order = (int *)malloc(sizeof(int) *
					data->param.nb_sprites)) || !(data->sprite.dist =
					(double *)malloc(sizeof(double) * data->param.nb_sprites)))
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
		while (data->param.map.tab_map[i][j] != '\0')
		{
			if (data->param.map.tab_map[i][j] > '1')
			{
				data->tab_sprite[k].sprite_y = (double)i + 0.5;
				data->tab_sprite[k].sprite_x = (double)j + 0.5;
				if (data->param.map.tab_map[i][j] == '2')
					data->tab_sprite[k].img.addr = data->sprite.img.addr;
				if (data->param.map.tab_map[i][j] == '3')
					data->tab_sprite[k].img.addr = data->sprite2.img.addr;
				k++;
			}
			j++;
		}
		i++;
	}
}

void	initialize_data_for_sprites(t_data *data, int i)
{
	data->sprite.pos_x = data->tab_sprite[data->sprite.order[i]].sprite_x - data->ray.pos_y;
	data->sprite.pos_y = data->tab_sprite[data->sprite.order[i]].sprite_y - data->ray.pos_x;
	data->sprite.invdet = 1.0 / (data->ray.plan_x * data->ray.dir_y -
			data->ray.dir_x * data->ray.plan_y);
	data->sprite.transform_x = data->sprite.invdet * (data->ray.dir_y * data->sprite.pos_x -
			data->ray.dir_x * data->sprite.pos_y);
	data->sprite.transform_y = data->sprite.invdet * (-data->ray.plan_y * data->sprite.pos_x +
			data->ray.plan_x * data->sprite.pos_y);
	data->sprite.screen = (int)((data->param.resolution.axe_x / 2) * (1 +
				data->sprite.transform_x / data->sprite.transform_y));
	data->sprite.height = abs((int)(data->param.resolution.axe_y /
				data->sprite.transform_y));
	data->sprite.draw_start_y = -data->sprite.height / 2 +
		data->param.resolution.axe_y / 2;
}

void	free_sprites(t_data *data)
{
	if (data->sprite.img.img)
		mlx_destroy_image(data->mlx_ptr, data->sprite.img.img);
//	if (data->param.bonus == '1' && data->sprite2.img.img)
//		mlx_destroy_image(data->mlx_ptr, data->sprite2.img.img);
	if (data->sprite.z_buffer)
		free(data->sprite.z_buffer);
	// if (data->tab_sprite.sprite_x)
	// 	free(data->tab_sprite.sprite_x);
	// if (data->tab_sprite.sprite_y)
	// 	free(data->tab_sprite.sprite.sprite_y);
	// if (data->sprite.order)
	// 	free(data->sprite.order);
	// if (data->sprite.dist)
	// 	free(data->sprite.dist);
	// if (data->sprite2.sprite_x)
	// 	free(data->sprite2.sprite_x);
	// if (data->sprite2.sprite_y)
	// 	free(data->sprite2.sprite_y);
	// if (data->sprite2.order)
	// 	free(data->sprite2.order);
	// if (data->sprite2.dist)
	// 	free(data->sprite2.dist);
}
