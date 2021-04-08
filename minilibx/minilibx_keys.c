#include "../include/struct_cub3d.h"
#include "../include/cub3d.h"

int		press_key(int key, t_data *data)
{
	if (key == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
		free_address_params(&data->param);
	}
	else if (key == ROTATE_LEFT_ARROW || key == ROTATE_LEFT_Q)
		ft_rotate_camera(key, data);
	else if (key == ROTATE_RIGHT_ARROW || key == ROTATE_RIGHT_E)
		ft_rotate_camera(key, data);
	if (key == FORWARD_W)
	{
		data->param.perso.dirx = 1 * cos(data->param.perso.angle * M_PI / 180);
		data->param.perso.diry = 1 * sin(data->param.perso.angle * M_PI / 180);
	}
	else if (key == BACK_S)
	{
		data->param.perso.dirx = -1 * cos(data->param.perso.angle * M_PI / 180);
		data->param.perso.diry = -1 * sin(data->param.perso.angle * M_PI / 180);
	}
	else if (key == RIGHT_D)
	{
		data->param.perso.dirx = -1 * sin(data->param.perso.angle * M_PI / 180);
		data->param.perso.diry = -1 * cos(data->param.perso.angle * M_PI / 180);
	}
	else if (key == LEFT_A)
	{
		data->param.perso.dirx = 1 * sin(data->param.perso.angle * M_PI / 180);
		data->param.perso.diry = 1 * cos(data->param.perso.angle * M_PI / 180);
	}
	return (0);
}

void	ft_rotate_camera(int key, t_data *data)
{
	double old_dirx;
	double old_planx;

	old_planx = data->ray.plan_x;
	old_dirx = data->ray.dir_x;
	if (key == ROTATE_LEFT_ARROW || key == ROTATE_LEFT_Q)
	{
		data->ray.dir_x = data->ray.dir_x * cos(-15 * M_PI / 180) -
			data->ray.dir_y * sin(-15 * M_PI / 180);
		data->ray.dir_y = old_dirx * sin(-15 * M_PI / 180) + data->ray.dir_y *
			cos(-15 * M_PI / 180);
		data->ray.plan_x = data->ray.plan_x * cos(-15 * M_PI / 180) -
			data->ray.plan_y * sin(-15 * M_PI / 180);
		data->ray.plan_y = old_planx * sin(-15 * M_PI / 180) + data->ray.plan_y
			* cos(15 * M_PI / 180);
		data->param.perso.angle -= 15;
		if (data->param.perso.angle < 0)
			data->param.perso.angle += 360;
	}
	else if (key == ROTATE_RIGHT_ARROW || key == ROTATE_RIGHT_E)
	{
		ft_rotate_camera(key, data);
		data->ray.dir_x = data->ray.dir_x * cos(15 * M_PI / 180) -
			data->ray.dir_y * sin(15 * M_PI / 180);
		data->ray.dir_y = old_dirx * sin(15 * M_PI / 180) + data->ray.dir_y *
			cos(15 * M_PI / 180);
		data->ray.plan_x = data->ray.plan_x * cos(15 * M_PI / 180) -
			data->ray.plan_y * sin(15 * M_PI / 180);
		data->ray.plan_y = old_planx * sin(15 * M_PI / 180) +
			data->ray.plan_y * cos(15 * M_PI / 180);
		data->param.perso.angle += 15;
		if (data->param.perso.angle >= 360)
			data->param.perso.angle -= 360;
	}
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

int		click_close(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	data->win_ptr = NULL;
	free_address_params(&data->param);
	return (0);
}
