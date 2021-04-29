#include "../include/struct_cub3d.h"
#include "../include/cub3d.h"

int		move_perso(t_data *data)
{
	float	speed;
	float	dist;
	int		x;
	int		y;

	speed = data->param.perso.speed;
	dist = 0.5;
	x = data->param.perso.position_y + data->param.perso.diry * speed +
		data->param.perso.diry * dist;
	y = data->param.perso.position_x + data->param.perso.dirx * speed +
		data->param.perso.dirx * dist;
	if (data->param.map.tab_map[x][y] == '2')
		data->bonus.life -= 1;
	if (data->param.map.tab_map[x][y] == '3')
	{
		if (data->bonus.life < 4)
			data->bonus.life += 1;
	}
	if ((check_speed(data) == 0) && (data->param.map.tab_map[x][y] == '0'
			|| data->param.map.tab_map[x][y] == data->param.perso.orientation))
	{
		data->param.perso.position_x += data->param.perso.dirx * speed;
		data->param.perso.position_y += data->param.perso.diry * speed;
	}
	return (0);
}

int		check_speed(t_data *data)
{
	int		x;
	int		y;

	x = data->param.perso.position_y + data->param.perso.diry * 0.01 +
		data->param.perso.diry * 0.01;
	y = data->param.perso.position_x + data->param.perso.dirx * 0.01 +
		data->param.perso.dirx * 0.01;
	if (data->param.map.tab_map[x][y] == '1')
			return (-1);
	return (0);
}

int		launch_hook(t_data *data)
{
	data->ray.pos_x = (double)data->param.perso.position_y;
	data->ray.pos_y = (double)data->param.perso.position_x;
	if (data->win_ptr == NULL)
		return (-1);
	raycasting(data, &data->ray);
	if (health_management(data) == -1)
	{
		close_game(data);
		return (-1);
	}
	play_music(data);
	draw_minimap(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.img, 0, 0);
	if (data->param.perso.dirx != 0 || data->param.perso.diry != 0)
		move_perso(data);
	mlx_destroy_image(data->mlx_ptr, data->img.img);
	data->img.img = mlx_new_image(data->mlx_ptr,
			data->param.resolution.axe_x,
			data->param.resolution.axe_y);
	data->img.addr = mlx_get_data_addr(data->img.img,
			&data->img.bits_per_pixel, &data->img.line_lenght,
			&data->img.endian);
	return (0);
}

int		create_window(t_data *data)
{
	int lenght;
	int width;

	data->mlx_ptr = mlx_init();
	if (data->mlx_ptr == NULL)
	{
		print_error(&data->param, "Couldn't start mlx_init");
		return (-1);
	}
	mlx_get_screen_size(data->mlx_ptr, &lenght, &width);
	if (lenght < data->param.resolution.axe_x)
		data->param.resolution.axe_x = lenght;
	if (width - 50 < data->param.resolution.axe_y)
		data->param.resolution.axe_y = width - 50;
	data->win_ptr = mlx_new_window(data->mlx_ptr, data->param.resolution.axe_x,
			data->param.resolution.axe_y, "my window");
	if (data->win_ptr == NULL)
	{
		free(data->win_ptr);
		print_error(&data->param, "Couldn't open a window");
		return (-1);
	}
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
			print_error(&data->param, "Initialisation failed");
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
