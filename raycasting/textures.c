/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 20:27:05 by llescure          #+#    #+#             */
/*   Updated: 2021/05/03 20:27:08 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/struct_cub3d.h"
#include "../include/cub3d.h"

void	ft_get_addr_textures(t_data *data)
{
	if (!(data->tab_texture[0].img = mlx_xpm_file_to_image(data->mlx_ptr,
					data->param.north_texture, &(data->tab_texture[0].width),
					&(data->tab_texture[0].height))))
		print_error_2(&data->param, "Error with texture");
	if (!(data->tab_texture[1].img = mlx_xpm_file_to_image(data->mlx_ptr,
					data->param.south_texture, &(data->tab_texture[1].width),
					&(data->tab_texture[1].height))))
		print_error_2(&data->param, "Error with texture");
	if (!(data->tab_texture[2].img = mlx_xpm_file_to_image(data->mlx_ptr,
					data->param.east_texture, &(data->tab_texture[2].width),
					&(data->tab_texture[2].height))))
		print_error_2(&data->param, "Error with texture");
	if (!(data->tab_texture[3].img = mlx_xpm_file_to_image(data->mlx_ptr,
					data->param.west_texture, &(data->tab_texture[3].width),
					&(data->tab_texture[3].height))))
		print_error_2(&data->param, "Error with texture");
	if (!(data->sprite1.img = mlx_xpm_file_to_image(data->mlx_ptr,
					data->param.sprite_1, &(data->sprite1.width),
					&(data->sprite1.height))))
		print_error_2(&data->param, "Error with texture");
	if (data->param.bonus == '1')
		get_sprites2_img(data);
	else
		data->sprite2.img = NULL;
}

void	get_textures(t_data *data)
{
	ft_get_addr_textures(data);
	data->tab_texture[0].addr = mlx_get_data_addr(data->tab_texture[0].img,
			&data->tab_texture[0].bits_per_pixel, &data->tab_texture[0].
			line_length, &data->tab_texture[0].endian);
	data->tab_texture[1].addr = mlx_get_data_addr(data->tab_texture[1].img,
			&data->tab_texture[1].bits_per_pixel, &data->tab_texture[1].
			line_length, &data->tab_texture[1].endian);
	data->tab_texture[2].addr = mlx_get_data_addr(data->tab_texture[2].img,
			&data->tab_texture[2].bits_per_pixel, &data->tab_texture[2].
			line_length, &data->tab_texture[2].endian);
	data->tab_texture[3].addr = mlx_get_data_addr(data->tab_texture[3].img,
			&data->tab_texture[3].bits_per_pixel,
			&data->tab_texture[3].line_length,
			&data->tab_texture[3].endian);
	data->sprite1.addr = mlx_get_data_addr(data->sprite1.img,
			&data->sprite1.bits_per_pixel, &data->sprite1.line_length,
			&data->sprite1.endian);
}

void	direction_texture(t_data *data)
{
	if (data->ray.side == 0 && data->ray.ray_dirx < 0)
		data->texture.text_dir = 0;
	if (data->ray.side == 0 && data->ray.ray_dirx >= 0)
		data->texture.text_dir = 1;
	if (data->ray.side == 1 && data->ray.ray_diry >= 0)
		data->texture.text_dir = 2;
	if (data->ray.side == 1 && data->ray.ray_diry < 0)
		data->texture.text_dir = 3;
	if (data->ray.side == 0)
		data->texture.wallx = data->ray.pos_y + data->ray.perp_wall_dist *
			data->ray.ray_diry;
	else
		data->texture.wallx = data->ray.pos_x + data->ray.perp_wall_dist *
			data->ray.ray_dirx;
	data->texture.wallx -= floor((data->texture.wallx));
}

void	draw_texture_walls(t_data *data, int pos_x)
{
	int y;
	int img_cord;
	int text_cord;

	y = data->ray.draw_start;
	initialize_before_drawing(data);
	while (y < data->ray.draw_end)
	{
		data->texture.y = (int)data->texture.position;
		data->texture.position += data->texture.step;
		img_cord = pos_x * 4 + 4 * data->param.resolution.axe_x * y;
		text_cord = data->texture.y * data->tab_texture[data->texture.text_dir].
			height * 4 + data->texture.x * 4;
		data->img.addr[img_cord] = shadow_texture(data->ray.perp_wall_dist,
			data->tab_texture[data->texture.text_dir].addr[text_cord]);
		data->img.addr[img_cord + 1] = shadow_texture(data->ray.perp_wall_dist,
			data->tab_texture[data->texture.text_dir].addr[text_cord + 1]);
		data->img.addr[img_cord + 2] = shadow_texture(data->ray.perp_wall_dist,
			data->tab_texture[data->texture.text_dir].addr[text_cord + 2]);
		data->img.addr[img_cord + 3] = shadow_texture(data->ray.perp_wall_dist,
			data->tab_texture[data->texture.text_dir].addr[text_cord + 3]);
		y++;
	}
}
