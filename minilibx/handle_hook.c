/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hook.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/27 14:40:45 by llescure          #+#    #+#             */
/*   Updated: 2021/03/27 16:53:14 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/struct_cub3D.h"
#include "../include/cub3D.h"

int	move_perso(t_data *data)
{
	if (data->param.map.tab_map[(int)(data->param.perso.position_y +
				data->param.perso.diry * 0.2)][(int)
			(data->param.perso.position_x + data->param.perso.dirx * 0.2)]
			== '0' || data->param.map.tab_map[(int)
			(data->param.perso.position_y + data->param.perso.diry * 0.2)]
			[(int)(data->param.perso.position_x +
				data->param.perso.dirx * 0.2)] ==
			data->param.perso.orientation)
	{
		data->param.perso.position_x +=	data->param.perso.dirx * 0.2;
		data->param.perso.position_y +=	data->param.perso.diry * 0.2;
	}
	//	printf("posx = %f\n", data->param.perso.position_x);
	//	printf("posy = %f\n",  data->param.perso.position_y);
	//	printf("angle = %f\n",  data->param.perso.angle);
	printf("pos_map = %c\n",  data->param.map.tab_map[(int)data->param.perso.position_y]
			[(int)data->param.perso.position_x]);
	return (0);
}

int	launch_hook(t_data *data)
{
	if (data->win_ptr == NULL)
		return (-1);
	draw_minimap(data);
	if (data->param.perso.dirx != 0 && data->param.perso.diry != 0)
		move_perso(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
	mlx_destroy_image(data->mlx_ptr, data->img.img);
	data->img.img = mlx_new_image(data->mlx_ptr, data->param.resolution.axe_x,
			data->param.resolution.axe_y);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
			&data->img.line_lenght, &data->img.endian);
	return (0);
}
