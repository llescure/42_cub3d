#include "../include/struct_cub3d.h"
#include "../include/cub3d.h"

void	get_image_by_sprite(t_data *data, t_sprite *sprite)
{
	if (sprite->type == '2')
		sprite->img = data->sprite1;
	else if (sprite->type == '3')
		sprite->img = data->sprite2;
}

void	initialize_data_for_sprites(t_data *data, t_sprite *sprite)
{
	sprite->pos_x = sprite->sprite_x - data->ray.pos_y;
	sprite->pos_y = sprite->sprite_y - data->ray.pos_x;
	sprite->invdet = 1.0 / (data->ray.plan_x * data->ray.dir_y -
			data->ray.dir_x * data->ray.plan_y);
	sprite->transform_x = sprite->invdet * (data->ray.dir_y * sprite->pos_x -
			data->ray.dir_x * sprite->pos_y);
	sprite->transform_y = sprite->invdet * (-data->ray.plan_y * sprite->pos_x +
			data->ray.plan_x * sprite->pos_y);
	sprite->screen = (int)((data->param.resolution.axe_x / 2) * (1 +
				sprite->transform_x / sprite->transform_y));
	sprite->height = abs((int)(data->param.resolution.axe_y /
				sprite->transform_y));
	sprite->draw_start_y = -sprite->height / 2 +
		data->param.resolution.axe_y / 2;
}

void	calculate_sprites(t_data *data, t_sprite *sprite)
{
	initialize_data_for_sprites(data, sprite);
	if (sprite->draw_start_y < 0)
		sprite->draw_start_y = 0;
	sprite->draw_end_y = sprite->height / 2 + data->param.resolution.axe_y / 2;
	if (sprite->draw_end_y >= data->param.resolution.axe_y)
		sprite->draw_end_y = data->param.resolution.axe_y - 1;
	sprite->width = abs((int)(data->param.resolution.axe_y /
		sprite->transform_y));
	sprite->draw_start_x = -sprite->width / 2 + sprite->screen;
	if (sprite->draw_start_x < 0)
		sprite->draw_start_x = 0;
	sprite->draw_end_x = sprite->width / 2 + sprite->screen;
	if (sprite->draw_end_x >= data->param.resolution.axe_x)
		sprite->draw_end_x = data->param.resolution.axe_x - 1;
}
