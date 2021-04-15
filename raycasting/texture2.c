int direction_texture(t_data *data)
{
	if (data->ray.side == 0 && data->ray.ray_dirx < 0)
		data->texture.text_dir = 0;
	if (data->ray.side == 0 && data->ray.ray_dirx >= 0)
		data->texture.text_dir = 1;
	if (data->ray.side == 1 && data->ray.ray_dirx < 0)
		data->texture.text_dir = 2;
	if (data->ray.side == 1 && data->ray.ray_dirx >= 0)
		data->texture.text_dir = 3;
	if (data->ray.side == 0)
		data->texture.wallx = data->ray.pos_y + data->ray.perp_wall_dist * data->ray.ray_diry;
	else
		data->texture.wallx = data->ray.pos_x + data->ray.perp_wall_dist * data->ray.ray_dirx;
	data->texture.wallx = data->texture.wallx - floor(data->texture.wallx);
}

int ft_get_addr_textures(t_data *data)
{
	data->img.width = 64;
	data->img.height = 64;
	if (!(data->tab_texture[0] = mlx_xpm_file_to_image(data->mlx_ptr,
					data->param.north_texture, &data->texture.text_width, &data->texture.text_height)))
		exit (0);
	if (!(data->tab_texture[1] = mlx_xpm_file_to_image(data->mlx_ptr,
					data->param.south_texture, &data->texture.text_width, &data->texture.text_width)))
		exit (0);
	if (!(data->tab_texture[2] = mlx_xpm_file_to_image(data->mlx_ptr,
					data->param.east_texture, &data->texture.text_width, &data->texture.text_width)))
		exit (0);
	if (!(data->tab_texture[3] = mlx_xpm_file_to_image(data->mlx_ptr,
					data->param.west_texture, &data->texture.text_width, &data->texture.text_width)))
		exit (0);
	if (!(data->tab_texture[4] = mlx_xpm_file_to_image(data->mlx_ptr,
					data->param.sprite, &data->texture.sprite_width, &data->texture.sprite_height)))
		exit (0);
	return (0);
}

int draw_texture_walls(t_data *data, int pos_x)
{
	int y;

	y = data->ray.draw_start - 1;
	direction_texture(data);
	data->texture.step = 1.0 * data->tab_texture[0].height / data->ray.line_height;
	data->texture.x = (int)(data->texture.wallx * (double)data->tab_texture[data->texture.text_dir].width);
	if (data->ray.side == 0 && data->ray.ray_dirx > 0)
		data->texture.x = data->tab_texture[data->texture.text_dir].width - data->texture.x - 1;
	if (data->ray.side == 1 && data->ray.ray_diry < 0)
		data->texture.x = data->tab_texture[data->texture.text_dir].width - data->texture.x - 1;
	data->texture.position = (data->ray.draw_start - data->resolution.axe_y / 2 + data->ray.line_height / 2) * data->texture.step;
	while (y <= data->ray.draw_end)
	{
		data->texture.y = (int)data->texture.position &
			(data->tab_texture[data->texture.text_dir].height - 1);
		data->texture.position += data->texture.step;
		if (y < data->param.resolution.axe_y && pos_x < data->param.resolution.axe_x)
			data->tab_texture[data->texture.text_dir].sddr[data->texture.y * data->texture[data->texture.text_dir].line_lenght / 4 + data->texture.x]
	}
	return (0);
}

void	free_textures(t_data *data)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (data->tab_textures[i].img)
			mlx_destroy_image(data->mlx_ptr, tab_textures[i].img);
		i++;
	}
}
