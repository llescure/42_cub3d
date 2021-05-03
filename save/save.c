/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 20:25:10 by llescure          #+#    #+#             */
/*   Updated: 2021/05/03 20:25:12 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include "../include/struct_cub3d.h"

int		create_image(t_data *data)
{
	int		fd;
	int		nbr_bits;

	nbr_bits = 0;
	if (check_resolution(&data->param) == -1)
		return (-1);
	if ((fd = open("./screenshot.bmp", O_CREAT | O_WRONLY, 0777)) == -1)
	{
		print_error(&data->param, "Couldn't create a bmp image");
		return (-1);
	}
	if (launch_mlx(data) == -1)
		return (-1);
	initialize_parameters_for_mlx(data);
	data->ray.pos_x = (double)data->param.perso.position_y;
	data->ray.pos_y = (double)data->param.perso.position_x;
	raycasting(data, &data->ray);
	draw_minimap(data);
	create_file_header(fd, data, &nbr_bits);
	create_info_header(fd, data, &nbr_bits);
	create_pixel_on_bmp(fd, data, &nbr_bits);
	return (close_bmp_file(fd, nbr_bits, data));
}

int		launch_mlx(t_data *data)
{
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
	{
		print_error(&data->param, "Couldn't start mlx_init");
		return (-1);
	}
	return (0);
}

int		check_resolution(t_param *param)
{
	if (param->resolution.axe_x > 2000 || param->resolution.axe_y > 2000)
	{
		print_error(param, "Resolution too high to be saved");
		return (-1);
	}
	return (0);
}

int		close_bmp_file(int fd, int nbr_bits, t_data *data)
{
	if (nbr_bits < 14 + 40)
	{
		print_error(&data->param, "Couldn't write on the file");
		return (-1);
	}
	if (close(fd) == -1)
	{
		print_error(&data->param, "Couldn't close the bmp image");
		return (-1);
	}
	free_address_params(&data->param);
	free_textures(data);
	mlx_destroy_image(data->mlx_ptr, data->img.img);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	printf("Image saved at ./screenshot.bmp\n");
	return (0);
}
