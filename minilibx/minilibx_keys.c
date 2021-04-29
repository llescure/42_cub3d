#include "../include/struct_cub3d.h"
#include "../include/cub3d.h"

int		press_key(int key, t_data *data)
{
	if (key == XK_Escape)
		close_game(data);
	else if (key == ROTATE_LEFT_ARROW || key == ROTATE_LEFT_Q)
		rotate_camera_left(data);
	else if (key == ROTATE_RIGHT_ARROW || key == ROTATE_RIGHT_E)
		rotate_camera_right(data);
	if (key == FORWARD_W)
		forward_backward_movement(1, &data->param.perso);
	else if (key == BACK_S)
		forward_backward_movement(-1, &data->param.perso);
	else if (key == RIGHT_D)
		left_right_movement(1, &data->param.perso);
	else if (key == LEFT_A)
		left_right_movement(-1, &data->param.perso);
	if (key == SPEED_ARROW)
		data->param.perso.speed = 0.01;
	else if (key == SLOW_ARROW)
		data->param.perso.speed = 0.5;
	else if (key == NORMAL_SPACE)
		data->param.perso.speed = 0.1;
	return (0);
}

int		close_game(t_data *data)
{
	int return_value;

	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	data->win_ptr = NULL;
	free_textures(data);
	free_address_params(&data->param);
	return_value = system("killall aplay");
	free(data->img.sound);
	return (return_value);
}

int		release_key(int key, t_data *data)
{
	if (key == FORWARD_W || key == BACK_S || key == RIGHT_D || key == LEFT_A)
	{
		data->param.perso.dirx = 0;
		data->param.perso.diry = 0;
	}
	return (0);
}
