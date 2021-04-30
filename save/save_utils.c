#include "../include/cub3d.h"
#include "../include/struct_cub3d.h"

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
	height = data->param.resolution.axe_y;
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

	y = data->param.resolution.axe_y;
	while (y >= 0)
	{
		x = 0;
		while (x < data->param.resolution.axe_x)
		{
			*nbr_bits += write(fd, &data->img.addr[4 * y *
					data->param.resolution.axe_x + 4 * x], 4);
			x++;
		}
		y--;
	}
}
