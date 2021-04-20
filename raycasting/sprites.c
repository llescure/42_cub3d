#include "../include/struct_cub3d.h"
#include "../include/cub3d.h"

void	order_sprite(t_data *data)
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
	while (i < data->param.nb_sprites)
	{
		data->sprite.order[i] = i;
		data->sprite.dist[i] = ((data->ray.pos_x - data->sprite.sprite_y[i]) *
				(data->ray.pos_x - data->sprite.sprite_y[i]) + (data->ray.pos_y -
					data->sprite.sprite_x[i]) * (data->ray.pos_y - data->sprite.sprite_x[i]));
		i++;
	}
	order_sprite(data);
}

void	calculate_sprites(t_data *data, int i)
{
	data->sprite.pos_x = data->sprite.sprite_x[data->sprite.order[i]] - data->ray.pos_y;
	data->sprite.pos_y = data->sprite.sprite_y[data->sprite.order[i]] - data->ray.pos_x;
	data->sprite.invdet = 1.0 / (data->ray.plan_x * data->ray.dir_y - data->ray.dir_x * data->ray.plan_y);
	data->sprite.transform_x = data->sprite.invdet * (data->ray.dir_y * data->sprite.pos_x - data->ray.dir_x * data->sprite.pos_y);
	data->sprite.transform_y = data->sprite.invdet * (-data->ray.plan_y * data->sprite.pos_x + data->ray.plan_x * data->sprite.pos_y);
	data->sprite.screen = (int)((data->param.resolution.axe_x / 2) * (1 + data->sprite.transform_x / data->sprite.transform_y));
	data->sprite.height = abs((int)(data->param.resolution.axe_y / data->sprite.transform_y));
	data->sprite.draw_start_y = -data->sprite.height / 2 + data->param.resolution.axe_y / 2;
	if (data->sprite.draw_start_y < 0)
		data->sprite.draw_start_y = 0;
	data->sprite.draw_end_y = data->sprite.height / 2 + data->param.resolution.axe_y / 2;
	if (data->sprite.draw_end_y >= data->param.resolution.axe_y)
		data->sprite.draw_end_y = data->param.resolution.axe_y - 1;
	data->sprite.width = abs((int)(data->param.resolution.axe_y / data->sprite.transform_y));
	data->sprite.draw_start_x = -data->sprite.width / 2 + data->sprite.screen;
	if (data->sprite.draw_start_x < 0)
		data->sprite.draw_start_x = 0;
	data->sprite.draw_end_x = data->sprite.width / 2 + data->sprite.screen;
	if (data->sprite.draw_end_x >= data->param.resolution.axe_x)
		data->sprite.draw_end_x = data->param.resolution.axe_x - 1;
	// printf("drawend_y = %d, drawstart_y = %d, drawend_x = %d, drawstart_x = %d\n", data->sprite.draw_end_y, data->sprite.draw_start_y, data->sprite.draw_end_x, data->sprite.draw_start_x);
}

void	draw_sprite(t_data *data, int stripe, int text_x, int text_y)
{
	int i;
	int d;

	i = data->sprite.draw_start_y - 1;
	while (++i < data->sprite.draw_end_y)
	{
		d = i * 256 - data->param.resolution.axe_y * 128 + data->sprite.height * 128;
		text_y = ((d * data->sprite.img.height) / data->sprite.height) / 256;
		// printf("textx = %i, texty = %i\n", text_x, text_y);
		// printf("d = %i\n", d);
		// printf("data->sprite.img.height = %i\n", data->sprite.img.height);
		// printf("data->sprite.height = %i\n", data->sprite.height);
		// printf("data->sprite.img.addr[4 * text_y * data->sprite.img.height + 4 * text_x] = %i\n", data->sprite.img.addr[4 * text_y * data->sprite.img.height + 4 * text_x]);
		if (data->sprite.img.addr[4 * text_y * data->sprite.img.height + 4 * text_x]) // si c'est transparent
			data->img.addr[4 * stripe + 4 * data->param.resolution.axe_x * i] =
				data->sprite.img.addr[4 * text_y * data->sprite.img.height + 4 * text_x];
		if (data->sprite.img.addr[text_y * data->sprite.img.height * 4 + text_x * 4 + 1]) // si c'est rouge
			data->img.addr[4 * stripe + 4 * data->param.resolution.axe_x * i + 1] =
				data->sprite.img.addr[text_y * data->sprite.img.height * 4 + text_x * 4 + 1];
		if (data->sprite.img.addr[text_y * data->sprite.img.height * 4 + text_x * 4 + 2]) // si c'est vert
			data->img.addr[4 * stripe + 4 * data->param.resolution.axe_x * i + 2] =
				data->sprite.img.addr[text_y * data->sprite.img.height * 4 + text_x * 4 + 2];
		if (data->sprite.img.addr[text_y * data->sprite.img.height * 4 + text_x * 4 + 3]) // si c'est bleu
			data->img.addr[4 * stripe + 4 * data->param.resolution.axe_x * i + 3] =
				data->sprite.img.addr[text_y * data->sprite.img.height * 4 + text_x * 4 + 3];
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
		calculate_sprites(data, i);
		stripe = data->sprite.draw_start_x - 1;
		while (++stripe < data->sprite.draw_end_x)
		{
			text_x = (int)(256 * (stripe - (-data->sprite.width / 2 + data->sprite.screen)) * data->sprite.img.width / data->sprite.width) / 256;
			// printf("data->sprite.width = %i\n", data->sprite.width);
			// printf("transform_y = %f, stripe = %i\n", data->sprite.transform_y, stripe);
			if (data->sprite.transform_y > 0 && stripe > 0 && stripe < data->param.resolution.axe_x && data->sprite.transform_y < data->sprite.z_buffer[stripe])
				draw_sprite(data, stripe, text_x, 0);
		}
	}
}

void		get_sprites_info(t_data *data)
{
  int i;
  int j;
  int k;

  k = 0;
  if (!(data->sprite.sprite_x = (double *)malloc(sizeof(double) * data->param.nb_sprites)) ||
   			!(data->sprite.sprite_y = (double *)malloc(sizeof(double) * data->param.nb_sprites)) ||
			!(data->sprite.order = (int *)malloc(sizeof(int) * data->param.nb_sprites)) ||
			!(data->sprite.dist = (double *)malloc(sizeof(double) * data->param.nb_sprites)))
	   print_error(&data->param, "sprites failed");
  i = 0;
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
		   j++;
	   }
	   i++;
  }
}
