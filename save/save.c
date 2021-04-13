#include "../include/cub3d.h"
#include "../include/struct_cub3d.h"

int		create_image(t_data *data)
{
	int		fd;

	if ((fd = open("./screenshot.bmp", O_CREAT | O_WRONLY | O_APPEND)) == -1)
	{
		printf("ERROR\nCouldn't create a bmp image");
		return (-1);
	}
	data->param.perso.dirx = 0;
	data->param.perso.diry = 0;
	raycasting(data, &data->ray);
	draw_minimap(data);
	create_file_header(fd, data);
	if (close(fd) == -1)
	{
		printf("ERROR\nCouldn't close the bmp image");
		return (-1);
	}
	return (0);
}

void	create_file_header(int fd, t_data *data)
{
	int bmp_integer;

	write(fd, "BM", 2);
	bmp_integer = 14 + 40 + 4 * data->param.resolution.axe_x *
	   data->param.resolution.axe_y;
	write(fd, &bmp_integer, 4);
	bmp_integer = 0;
	write(fd, &bmp_integer, 2);
	write(fd, &bmp_integer, 2);
	bmp_integer = 54;
	write(fd, &bmp_integer, 4);
}

void	create_info_header(int fd, t_data *data)
{
	int bmp_integer;
	int width;
	int height;

	bmp_integer = 40;
	write(fd, &bmp_integer, 4);
	width = data->param.resolution.axe_x;
	write(fd, &width, 4);
	height = data ->param.resolution.axe_y;
	write(fd, &height, 4);
	bmp_integer = 1;
	write(fd, &bmp_integer, 2);
	write(fd, &data->img.bits_per_pixel, 2);
	bmp_integer = 0;
	write(fd, &bmp_integer, 4);
	write(fd, &bmp_integer, 4);
	write(fd, &bmp_integer, 4);
	write(fd, &bmp_integer, 4);
	write(fd, &bmp_integer, 4);
	write(fd, &bmp_integer, 4);
}
