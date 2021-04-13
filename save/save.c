#include "../include/cub3d.h"
#include "../include/struct_cub3d.h"

int		create_image(t_data *data)
{
	int		fd;

	if ((fd = open("screenshot.bmp", O_CREAT | O_WRONLY | O_APPEND)) == -1)
	{
		printf("ERROR\nCouldn't create a bmp image");
		return (-1);
	}
	data->param.perso.dirx = 0;
	data->param.perso.diry = 0;
	raycasting(data, &data->ray);
	draw_minimap(data);
	if (close(fd) == -1)
	{
		printf("ERROR\nCouldn't close the bmp image");
		return (-1);
	}
}

void	create_file_header(int fd, t_data *data)
{
	int bmp_integer;

	write(fd, "BM", 2);
	bmp_integer = 0;
	write(fd, &bmp_integer, 2);
	write(fd, &bmp_integer, 2);
}
