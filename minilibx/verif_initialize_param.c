#include "../include/struct_cub3d.h"
#include "../include/cub3d.h"

int		check_for_lonely_walls(t_map map, int x, int y)
{
	if (x == map.nb_lines - 1 || y == map.max_length - 1 || x == 0 || y == 0)
		return (0);
	if ((map.tab_map[x + 1][y] == '1' && map.tab_map[x][y - 1] == '1') &&
		(map.tab_map[x + 1][y] == '1' && map.tab_map[x][y + 1] == '1') &&
		(map.tab_map[x - 1][y] == '1' && map.tab_map[x][y - 1] == '1') &&
		(map.tab_map[x - 1][y] == '1' && map.tab_map[x][y + 1] == '1'))
		return (-1);
	return (0);
}

void	initialize_parameters_for_mlx(t_data *data)
{
	int i;

	i = 0;
	data->param.perso.dirx = 0;
	data->param.perso.diry = 0;
	data->param.perso.speed = 0.1;
	get_health_level(data);
	initialisation_orientation(&data->param, &data->ray);
	data->img.img = mlx_new_image(data->mlx_ptr, data->param.resolution.axe_x,
			data->param.resolution.axe_y);
	data->img.addr = mlx_get_data_addr(data->img.img, &data->img.bits_per_pixel,
			&data->img.line_lenght, &data->img.endian);
	get_sprites_info(data);
	while (i < data->param.nb_sprites)
	{
		if (!(data->tab_sprite[i].z_buffer = (double *)malloc(sizeof(double)
				* data->param.resolution.axe_x)))
			print_error_2(&data->param, "Initialisation failed");
		i++;
	}
	get_textures(data);
	if (data->param.ceiling_texture != NULL)
		get_ceiling_textures(data);
	if (data->param.floor_texture != NULL)
		get_floor_textures(data);
}

int		initialize_mlx(t_data *data)
{
	initialize_parameters_for_mlx(data);
	mlx_hook(data->win_ptr, KeyPress, KeyPressMask, &press_key, data);
	mlx_hook(data->win_ptr, 33, (1L << 17), &close_game, data);
	mlx_hook(data->win_ptr, KeyRelease, KeyReleaseMask, &release_key, data);
	mlx_loop_hook(data->mlx_ptr, &launch_hook, data);
	mlx_loop(data->mlx_ptr);
	mlx_destroy_image(data->mlx_ptr, data->img.img);
	mlx_destroy_display(data->mlx_ptr);
	free(data->mlx_ptr);
	return (0);
}
