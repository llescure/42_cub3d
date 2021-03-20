#include "../include/struct_cub3D.h"
#include "../include/cub3D.h"

int	press_key(int key, t_data *data, t_ray *ray)
{
	if (key == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	else if (key == ROTATE_LEFT)
		ray->camerax = -1;
	else if (key == ROTATE_RIGHT)
		ray->camerax = 1;
	else if (key == FORWARD_W_Z)
		ray->diry = -1;
	else if (key == BACK_S_S)
		ray->diry = 1;
	else if (key == RIGHT_D_D)
		ray->dirx = 1;
	else if (key == LEFT_A_Q)
		ray->dirx = 1;
	return (0);
}

int	release_key(int key, t_ray *ray)
{
	if (key == ROTATE_LEFT)
		ray->camerax = 0;
	else if (key == ROTATE_RIGHT)
		ray->camerax = 0;
	else if (key == FORWARD_W_Z)
		ray->diry = 0;
	else if (key == BACK_S_S)
		ray->diry = 0;
	else if (key == RIGHT_D_D)
		ray->dirx = 0;
	else if (key == LEFT_A_Q)
		ray->dirx = 0;
	return (0);
}

int	click_close(t_data *data)
{
	mlx_destroy_window(data->mlx_ptr, data->win_ptr);
	data->win_ptr = NULL;
	return (0);
}
