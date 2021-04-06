void	ft_textures(t_data *data)
{
//	float	wdatax;

	// if (data->ray.side == 0)
	// 	wdatax = data->ray.posY + data->ray.perpWdallDist * data->ray.rayDirY;
	// else
	// 	wdatax = data->ray.posX + data->perpWdalldist * data->ray.rayDirX;
	// data->tex.x = (int)(wdatax * data->texheight);
	// if (data->ray.side == 0 && data->ray.rayDirX > 0)
	// 	data->tex.x = data->texwidth - data->tex.x - 1;
	// if (data->ray.side == 1 && data->ray.raydirY < 0)
	// 	data->tex.x = data->texwidth - data->tex.x - 1;
//	data->tex.step = 1.0 * data->texheight / data->ray.lineHeight;
//	data->tex.pos = (data->ray.drawStart - data->param.resolution.axe_y / 2 + data->ray.lineHeight / 2)
//	* data->tex.step;
	if (data->ray.side == 0 && (data->ray.mapX > data->ray.posX))
		data->texture.color = (int *)data->texture.text_south;
	else if (data->ray.side == 1 && (data->ray.mapY < data->ray.posY))
		data->texture.color = (int *)data->texture.text_west;
	else if (data->ray.side == 1 && (data->ray.mapY > data->ray.posY))
		data->texture.color = (int *)data->texture.text_east;
	else
		data->texture.color = (int *)data->texture.text_north;
	data->color = (int *)data->spr.tex;
}
