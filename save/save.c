#include "../include/cub3d.h"
#include "../include/struct_cub3d.h"

int		create_image(t_data *data)
{
	int		fd;
	int		nbr_bits;

	nbr_bits = 0;
	if ((fd = open("./screenshot.bmp", O_CREAT | O_WRONLY | O_APPEND, 0777))
			== -1)
	{
		printf("ERROR\nCouldn't create a bmp image");
		return (-1);
	}
	data->param.perso.dirx = 0;
	data->param.perso.diry = 0;
	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
	{
		printf("ERROR\nCouldn't start mlx_init");
		return (-1);
	}
	data->img.img = mlx_new_image(data->mlx_ptr, data->param.resolution.axe_x,
			data->param.resolution.axe_y);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
			&data->img.line_lenght, &data->img.endian);
//	raycasting(data, &data->ray);
	draw_minimap(data);
	create_file_header(fd, data, &nbr_bits);
	create_info_header(fd, data, &nbr_bits);
	create_pixel_on_bmp(fd, data, &nbr_bits);
	if (close_bmp_file(fd, nbr_bits, data) == -1)
		return (-1);
	return (0);
}

void	create_file_header(int fd, t_data *data, int *nbr_bits)
{
	int bmp_integer;

	*nbr_bits += write(fd, "BM", 2);
	bmp_integer = 14 + 40 + 4 * data->param.resolution.axe_x *
		data->param.resolution.axe_y;
	*nbr_bits += write(fd, &bmp_integer, 4);
	bmp_integer = 0;
	*nbr_bits += write(fd, &bmp_integer, 2);
	*nbr_bits += write(fd, &bmp_integer, 2);
	bmp_integer = 54;
	*nbr_bits += write(fd, &bmp_integer, 4);
}

void	create_info_header(int fd, t_data *data, int *nbr_bits)
{
	int bmp_integer;
	int width;
	int height;

	bmp_integer = 40;
	*nbr_bits += write(fd, &bmp_integer, 4);
	width = data->param.resolution.axe_x;
	*nbr_bits += write(fd, &width, 4);
	height = data ->param.resolution.axe_y;
	*nbr_bits += write(fd, &height, 4);
	bmp_integer = 1;
	*nbr_bits += write(fd, &bmp_integer, 2);
	*nbr_bits += write(fd, &data->img.bits_per_pixel, 2);
	bmp_integer = 0;
	*nbr_bits += write(fd, &bmp_integer, 4);
	*nbr_bits += write(fd, &bmp_integer, 4);
	*nbr_bits += write(fd, &bmp_integer, 4);
	*nbr_bits += write(fd, &bmp_integer, 4);
	*nbr_bits += write(fd, &bmp_integer, 4);
	*nbr_bits += write(fd, &bmp_integer, 4);
}

void	create_pixel_on_bmp(int fd, t_data *data, int *nbr_bits)
{
	int		x;
	int		y;
	char	*pixel;

	y = data->param.resolution.axe_y;
	(void)fd;
	(void)nbr_bits;
	while (y > 0)
	{
		x = 0;
		while (x < data->param.resolution.axe_x)
		{
			pixel = data->img.addr + (y * data->img.line_lenght + x * (data->img.bits_per_pixel / 8));
		//	printf("pointer %p\n", pixel);
			*(int *)pixel = BLUE_PIXEL;
		//	*nbr_bits = write(fd, &pixel, 1);
			x++;
		}
		y--;
	}
}

int		close_bmp_file(int fd, int nbr_bits, t_data *data)
{
	if (nbr_bits != 14 + 40 + 4 * data->param.resolution.axe_x *
			data->param.resolution.axe_y)
	{
		printf("ERROR\nCouldn't write on the file");
		return (-1);
	}
	if (close(fd) == -1)
	{
		printf("ERROR\nCouldn't close the bmp image");
		return (-1);
	}
	return (0);
}
