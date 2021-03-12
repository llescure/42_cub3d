#include "parsing/parsing.h"
#include "minilibx/minilibx.h"

int			main(int argc, char **argv)
{
	char	*str;
	char	*map;
	int		fd;
	t_data	data;
	t_param	param;

	if (!(map = malloc(sizeof(char) * 2)))
		return (-1);
	map[0] = 0;
	if (!(str = malloc(sizeof(char) * 2)))
		return (-1);
	initialize_structure(&param, argv[1]);
	fd = open(argv[1], O_RDONLY);
	manage_errors(argc, argv);
	read_map(fd, str, map, &param);
	print_params(&param);

	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (-1);
	data.win_ptr = mlx_new_window(data.mlx_ptr, param.resolution.axe_x, param.resolution.axe_y, "my window");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (-1);
	}
	data.img.img = mlx_new_image(data.mlx_ptr, param.resolution.axe_y, param.resolution.axe_y);
	data.img.addr = mlx_get_data_addr(data.img.img, &data.img.bits_per_pixel,
			&data.img.line_lenght, &data.img.endian);
	mlx_loop_hook(data.mlx_ptr, &draw, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &press_key, &data);
	mlx_hook(data.win_ptr, 33, (1L << 17), &click_close, &data);
	mlx_loop(data.mlx_ptr);
	mlx_destroy_image(data.mlx_ptr, data.img.img);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	free_address_params(&param);
	return (0);
}

