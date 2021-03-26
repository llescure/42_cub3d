#include "../include/struct_cub3D.h"
#include "../include/cub3D.h"

int	press_key(int key, t_data *data)
{
	if (key == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	else if (key == ROTATE_LEFT)
	{
		data->param.perso.angle -= 15;
		if (data->param.perso.angle < 0)
			data->param.perso.angle += 360;
	}
	else if (key == ROTATE_RIGHT)
	{
		data->param.perso.angle += 15;
		if (data->param.perso.angle >= 360)
			data->param.perso.angle -= 360;
	}
	else if (key == FORWARD_W_Z)
	{
		data->param.perso.dirx = 1 * cos(data->param.perso.angle * M_PI / 180);
		data->param.perso.diry = 1 * sin(data->param.perso.angle * M_PI / 180);
	}
	else if (key == BACK_S_S)
	{
		data->param.perso.dirx = -1 * cos(data->param.perso.angle * M_PI / 180);
		data->param.perso.diry = -1 *sin(data->param.perso.angle * M_PI / 180);
	}
	else if (key == RIGHT_D_D)
	{
		data->param.perso.dirx = 1 * sin(data->param.perso.angle * M_PI / 180);
		data->param.perso.diry = 1 * cos(data->param.perso.angle * M_PI / 180);
	}
	else if (key == LEFT_A_Q)
	{
		data->param.perso.dirx = -1 * sin(data->param.perso.angle * M_PI / 180);
		data->param.perso.diry = -1 * cos(data->param.perso.angle * M_PI / 180);
	}
	return (0);
}

int	release_key(int key, t_data *data)
{
	if (key == ROTATE_LEFT || key == ROTATE_RIGHT)
		data->param.perso.angle += 0;
	else if (key == FORWARD_W_Z || key == BACK_S_S || RIGHT_D_D || LEFT_A_Q)
	{
		data->param.perso.dirx = 0;
		data->param.perso.diry = 0;
	}
	return (0);
}

int	click_close(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	data->win_ptr = NULL;
	return (0);
}
