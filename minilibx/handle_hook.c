/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 20:22:02 by llescure          #+#    #+#             */
/*   Updated: 2021/05/03 20:22:05 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/struct_cub3d.h"
#include "../include/cub3d.h"

int		move_perso(t_data *data)
{
	float	dist;
	int		x;
	int		y;

	dist = 0.5;
	x = data->param.perso.position_y + data->param.perso.diry *
		data->param.perso.speed + data->param.perso.diry * dist;
	y = data->param.perso.position_x + data->param.perso.dirx *
		data->param.perso.speed + data->param.perso.dirx * dist;
	if (data->param.map.tab_map[x][y] == '2')
		data->bonus.life -= 1;
	if (data->param.map.tab_map[x][y] == '3')
		if (data->bonus.life < 4)
			data->bonus.life += 1;
	if ((check_for_lonely_walls(data->param.map, x, y) == 0) &&
		(data->param.map.tab_map[x][y] == '0' ||
		data->param.map.tab_map[x][y] == data->param.perso.orientation))
	{
		data->param.perso.position_x += data->param.perso.dirx *
			data->param.perso.speed;
		data->param.perso.position_y += data->param.perso.diry *
			data->param.perso.speed;
	}
	return (0);
}

int		launch_hook(t_data *data)
{
	data->ray.pos_x = (double)data->param.perso.position_y;
	data->ray.pos_y = (double)data->param.perso.position_x;
	if (data->win_ptr == NULL)
		return (-1);
	raycasting(data, &data->ray);
	if (health_management(data) == -1)
	{
		close_game(data);
		return (-1);
	}
	play_music(data);
	draw_minimap(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
	if (data->param.perso.dirx != 0 || data->param.perso.diry != 0)
		move_perso(data);
	mlx_destroy_image(data->mlx_ptr, data->img.img);
	data->img.img = mlx_new_image(data->mlx_ptr,
			data->param.resolution.axe_x,
			data->param.resolution.axe_y);
	data->img.addr = mlx_get_data_addr(data->img.img,
			&data->img.bits_per_pixel, &data->img.line_length,
			&data->img.endian);
	return (0);
}

int		create_window(t_data *data)
{
	int length;
	int width;

	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
	{
		print_error_2(&data->param, "Couldn't start mlx_init");
		return (-1);
	}
	mlx_get_screen_size(data->mlx_ptr, &length, &width);
	if (length < data->param.resolution.axe_x)
		data->param.resolution.axe_x = length;
	if (width - 50 < data->param.resolution.axe_y)
		data->param.resolution.axe_y = width - 50;
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->param.resolution.axe_x,
			data->param.resolution.axe_y, "my window");
	if (data->win_ptr == NULL)
	{
		free(data->win_ptr);
		print_error_2(&data->param, "Couldn't open a window");
		return (-1);
	}
	return (0);
}
