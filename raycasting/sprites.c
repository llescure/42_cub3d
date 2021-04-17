#include "../include/struct_data3d.h"
#include "../include/data3d.h"

void	ft_sort_sprite(t_data *data)
{
	int		i;
	int		j;
	double	tmp;

	i = -1;
	while (++i < data->param.nb_sprites)
	{
		j = -1;
		while (++j < data->param.nb_sprites - 1)
			if (data->sprt_dist[j] < data->sprt_dist[j + 1])
			{
				tmp = data->sprt_dist[j];
				data->sprt_dist[j] = data->sprt_dist[j + 1];
				data->sprt_dist[j + 1] = tmp;
				tmp = data->sprt_order[j];
				data->sprt_order[j] = data->sprt_order[j + 1];
				data->sprt_order[j + 1] = (int)tmp;
			}
	}
}

void	ft_sprite_sorting(t_data *data)
{
	int i;

	i = -1;
	while (++i < data->param.nb_sprites)
	{
		data->sprt_order[i] = i;
		data->sprt_dist[i] = ((data->pos.x - data->sprt[i].x) *
				(data->pos.x - data->sprt[i].x) + (data->pos.y -
					data->sprt[i].y) * (data->pos.y - data->sprt[i].y));
	}
	ft_sort_sprite(data);
}

void	ft_set_cal_sprite(t_data *data, int i)
{
	data->spt_pos.x = data->sprt[data->sprt_order[i]].x - data->pos.x;
	data->spt_pos.y = data->sprt[data->sprt_order[i]].y - data->pos.y;
	data->invdet = 1.0 / (data->plane.x * data->dir.y - data->dir.x * data->plane.y);
	data->transform.x = data->invdet * (data->dir.y * data->spt_pos.x -
			data->dir.x * data->spt_pos.y);
	data->transform.y = data->invdet * (-data->plane.y * data->spt_pos.x +
			data->plane.x * data->spt_pos.y);
	data->spritescreenx = (int)((data->param.resolution.axe_x / 2) * (1 + data->transform.x /
				data->transform.y));
	data->sprite.height = abs((int)(data->param.resolution.axe_y / data->transform.y));
	data->sprite.draw_start_y = -data->sprite.height / 2 + data->param.resolution.axe_y / 2;
	data->sprite.draw_start_y = (data->sprite.draw_start_y < 0) ? 0 :
		data->sprite.draw_start_y;
	data->sprite.draw_end_y = data->sprite.height / 2 + data->param.resolution.axe_y / 2;
	data->sprite.draw_end_y = (data->sprite.draw_end_y >= data->param.resolution.axe_y) ?
		data->param.resolution.axe_y - 1 : data->sprite.draw_end_y;
	data->sprite.width = abs((int)(data->param.resolution.axe_y / data->transform.y));
	data->sprite.draw_start_x = -data->sprite.width / 2 + data->spritescreenx;
	data->sprite.draw_start_x = (data->sprite.draw_start_x < 0) ? 0 :
		data->sprite.draw_start_x;
	data->sprite.draw_end_x = data->sprite.width / 2 + data->spritescreenx;
	data->sprite.draw_end_x = (data->sprite.draw_end_x >= data->param.resolution.axe_x) ?
		data->param.resolution.axe_x - 1 : data->sprite.draw_end_x;
}

void	ft_draw_sprite(t_data *data, int stripe, int text_x, int text_y)
{
	int i;
	int d;
	int y;

	i = data->sprite.draw_start_y - 1;
	while (++i < data->sprite.draw_end_y)
	{
		d = i * 256 - data->param.resolution.axe_y * 128 + data->sprite.height * 128;
		text_y = ((d * data->sprite.img.height) / data->sprite.height) / 256;
		if (data->sprite.img.addr[4 * text_y * data->sprite.img.height + 4 * text_x]) // si c'est transparent
			data->img.addr[4 * stripe + 4 * data->param.resolution.axe_x * y] =
				data->sprite.img.addr[4 * text_y * data->sprite.img.height + 4 * text_x];
		if (data->sprite.img.addr[text_y * data->sprite.img.height * 4 + text_x * 4 + 1]) // si c'est rouge
			data->img.data[4 * stripe + 4 * data->param.resolution.axe_x * y + 1] =
				data->sprite.img.addr[text_y * data->sprite.img.height * 4 + text_x * 4 + 1];
		if (data->sprite.img.addr[text_y * data->sprite.img.height * 4 + text_x * 4 + 2]) // si c'est vert
			data->img.data[4 * stripe + 4 * data->param.resolution.axe_x * y + 2] =
				data->sprite.img.addr[text_y * data->sprite.img.height * 4 + text_x * 4 + 2];
		if (data->sprite.img.addr[text_y * data->sprite.img.height * 4 + text_x * 4 + 3]) // si c'est bleu
			data->img.addr[4 * stripe + 4 * data->param.resolution.axe_x * y + 3] =
				data->sprite.img.addr[text_y * data->sprite.img.heigh * 4 + text_x * 4 + 3];
	}
}

void	ft_sprite_casting(t_data *data)
{
	int	i;
	int	stripe;
	int	text_x;

	i = -1;
	ft_sprite_sorting(data);
	while (++i < data->param.nb_sprites)
	{
		ft_set_cal_sprite(data, i);
		stripe = data->sprite.draw_start_x - 1;
		while (++stripe < data->sprite.draw_end_x)
		{
			text_x = (int)(256 * (stripe - (-data->sprite.width / 2 +
							data->spritescreenx)) * data->sprite.img.width /
					data->sprite.width) / 256;
			if (data->transform.y > 0 && stripe > 0 && stripe < data->param.resolution.axe_x &&
					data->transform.y < data->z_buffer[stripe])
				ft_draw_sprite(data, stripe, text_x, 0);
		}
	}
}
