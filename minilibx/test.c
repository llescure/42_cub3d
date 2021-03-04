/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 12:16:27 by llescure          #+#    #+#             */
/*   Updated: 2021/02/15 14:46:19 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minilibx.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char *dst;

	dst = data->addr + (y * data->line_lenght + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int		main(void)
{
	t_img	img;
	t_data	data;

	data.mlx = mlx_init();
	data.mlx_win = mlx_new_window(data.mlx, 1920, 1080, "Hello world!");
	img.img = mlx_new_image(data.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_lenght,
			&img.endian);
	my_mlx_pixel_put(&img, 100, 100, 0x000000FF);
	mlx_put_image_to_window(data.mlx, data.mlx_win, img.img, 0, 0);
	mlx_loop(data.mlx);
}
