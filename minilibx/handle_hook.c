/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 14:40:45 by llescure          #+#    #+#             */
/*   Updated: 2021/03/29 15:43:39 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/struct_cub3D.h"
#include "../include/cub3D.h"

int	move_perso(t_data *data)
{
	if (data->param.map.tab_map[(int)(data->param.perso.position_y +
				data->param.perso.diry * 0.1)][(int)
			(data->param.perso.position_x + data->param.perso.dirx * 0.1)]
			== '0' || data->param.map.tab_map[(int)
			(data->param.perso.position_y + data->param.perso.diry * 0.1)]
			[(int)(data->param.perso.position_x +
				data->param.perso.dirx * 0.1)] ==
			data->param.perso.orientation)
	{
		data->param.perso.position_x +=	data->param.perso.dirx * 0.1;
		data->param.perso.position_y +=	data->param.perso.diry * 0.1;
	}
	return (0);
}

int	launch_hook(t_data *data)
{
	if (data->win_ptr == NULL)
		return (-1);
	draw_minimap(data);
	if (data->param.perso.dirx != 0 || data->param.perso.diry != 0)
		move_perso(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr,
			data->img_minimap.img, 0, 0);
	mlx_destroy_image(data->mlx_ptr, data->img_minimap.img);
	data->img_minimap.img = mlx_new_image(data->mlx_ptr,
			data->param.resolution.axe_x,
			data->param.resolution.axe_y);
	data->img_minimap.addr = mlx_get_data_addr(data->img_minimap.img,
			&data->img_minimap.bits_per_pixel, &data->img_minimap.line_lenght,
			&data->img_minimap.endian);
	return (0);
}
