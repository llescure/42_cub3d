#include "../include/struct_cub3D.h"
#include "../include/cub3D.h"

int	press_key(int key, t_data *data)
{
	if (key == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
		free_address_params(&data->param);
	}
	else if (key == ROTATE_LEFT_ARROW || key == ROTATE_LEFT_Q)
	{
		double oldDirX = data->ray.dirX;
		data->ray.dirX = data->ray.dirX * cos(0.1) - data->ray.dirY * sin(0.1);
		data->ray.dirY = oldDirX * sin(0.1) + data->ray.dirY * cos(0.1);
		double oldPlanX = data->ray.planX;
		data->ray.planX = data->ray.planX * cos(0.1) - data->ray.planY * sin(0.1);
		data->ray.planY = oldPlanX * sin(0.1) + data->ray.planY * cos(0.1);
		data->param.perso.angle -= 15;
		if (data->param.perso.angle < 0)
			data->param.perso.angle += 360;
	}
	else if (key == ROTATE_RIGHT_ARROW || key == ROTATE_RIGHT_E)
	{
		double oldDirX = data->ray.dirX;
		data->ray.dirX = data->ray.dirX * cos(-0.1) - data->ray.dirY * sin(-0.1);
		data->ray.dirY = oldDirX * sin(-0.1) + data->ray.dirY * cos(-0.1);
		double oldPlanX = data->ray.planX;
		data->ray.planX = data->ray.planX * cos(-0.1) - data->ray.planY * sin(-0.1);
		data->ray.planY = oldPlanX * sin(-0.1) + data->ray.planY * cos(0.1);
		data->param.perso.angle += 15;
		if (data->param.perso.angle >= 360)
			data->param.perso.angle -= 360;
	}
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
		data->param.perso.dirx = 1 * sin(data->param.perso.angle * M_PI / 180);
		data->param.perso.diry = 1 * cos(data->param.perso.angle * M_PI / 180);
	}
	else if (key == LEFT_A)
	{
		data->param.perso.dirx = -1 * sin(data->param.perso.angle * M_PI / 180);
		data->param.perso.diry = -1 * cos(data->param.perso.angle * M_PI / 180);
	}

/*	int moveSpeed = 0.1;
	int rotSpeed = 0.15;
	//move forward if no wall in front of you

	if (key == FORWARD_W)
	{
		if(data->param.map.tab_map[(int)(data->ray.posX + data->ray.dirX * moveSpeed)][(int)(data->ray.posY)] == '0')
			data->ray.posX += data->ray.dirX * moveSpeed;
		if(data->param.map.tab_map[(int)(data->ray.posX)][(int)(data->ray.posY + data->ray.dirY * moveSpeed)] == '0')
			data->ray.posY += data->ray.dirY * moveSpeed;
	}
	//move backwards if no wall behind you
	if (key == BACK_S)
	{
		if(data->param.map.tab_map[(int)(data->ray.posX - data->ray.dirX * moveSpeed)][(int)(data->ray.posY)] == '0')
			data->ray.posX -= data->ray.dirX * moveSpeed;
		if(data->param.map.tab_map[(int)(data->ray.posX)][(int)(data->ray.posY - data->ray.dirY * moveSpeed)] == '0')
			data->ray.posY -= data->ray.dirY * moveSpeed;
	}
	//rotate to the right
	if (key == ROTATE_RIGHT_ARROW || key == ROTATE_RIGHT_E)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = data->ray.dirX;
		data->ray.dirX = data->ray.dirX * cos(-rotSpeed) - data->ray.dirY * sin(-rotSpeed);
		data->ray.dirY = oldDirX * sin(-rotSpeed) + data->ray.dirY * cos(-rotSpeed);
		double oldPlanX = data->ray.planX;
		data->ray.planX = data->ray.planX * cos(-rotSpeed) - data->ray.planY * sin(-rotSpeed);
		data->ray.planY = oldPlanX * sin(-rotSpeed) + data->ray.planY * cos(-rotSpeed);
	}
	//rotate to the left
	if (key == ROTATE_LEFT_ARROW || key == ROTATE_LEFT_Q)
	{
		//both camera direction and camera plane must be rotated
		double oldDirX = data->ray.dirX;
		data->ray.dirX = data->ray.dirX * cos(rotSpeed) - data->ray.dirY * sin(rotSpeed);
		data->ray.dirY = oldDirX * sin(rotSpeed) + data->ray.dirY * cos(rotSpeed);
		double oldPlanX = data->ray.planX;
		data->ray.planX = data->ray.planX * cos(rotSpeed) - data->ray.planY * sin(rotSpeed);
		data->ray.planY = oldPlanX * sin(rotSpeed) + data->ray.planY * cos(rotSpeed);
	}*/
	return (0);
}

int	release_key(int key, t_data *data)
{
	if (key == FORWARD_W || key == BACK_S || key == RIGHT_D || key == LEFT_A)
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
	free_address_params(&data->param);
	return (0);
}
