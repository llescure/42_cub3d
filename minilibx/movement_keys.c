#include "../include/struct_cub3d.h"
#include "../include/cub3d.h"

void	rotate_camera_left(t_data *data)
{
	double old_dirx;
	double old_planx;
	double cosi;
	double sinus;

	old_planx = data->ray.plan_x;
	old_dirx = data->ray.dir_x;
	if (data->param.perso.orientation == 'N' ||
			data->param.perso.orientation == 'S')
	{
		cosi = cos(15 * M_PI / 180);
		sinus = sin(15 * M_PI / 180);
	}
	else
	{
		cosi = -cos(15 * M_PI / 180);
		sinus = -sin(15 * M_PI / 180);
	}
	data->ray.dir_x = data->ray.dir_x * cosi - data->ray.dir_y * sinus;
	data->ray.dir_y = old_dirx * sinus + data->ray.dir_y * cosi;
	data->ray.plan_x = data->ray.plan_x * cosi - data->ray.plan_y * sinus;
	data->ray.plan_y = old_planx * sinus + data->ray.plan_y * cosi;
}

void	rotate_camera_right(t_data *data)
{
	double old_dirx;
	double old_planx;
	double cosi;
	double sinus;

	old_planx = data->ray.plan_x;
	old_dirx = data->ray.dir_x;
	if (data->param.perso.orientation == 'N' ||
			data->param.perso.orientation == 'S')
	{
		cosi = cos(-15 * M_PI / 180);
		sinus = sin(-15 * M_PI / 180);
	}
	else
	{
		cosi = -cos(-15 * M_PI / 180);
		sinus = -sin(-15 * M_PI / 180);
	}
	data->ray.dir_x = data->ray.dir_x * cosi - data->ray.dir_y * sinus;
	data->ray.dir_y = old_dirx * sinus + data->ray.dir_y * cosi;
	data->ray.plan_x = data->ray.plan_x * cosi - data->ray.plan_y * sinus;
	data->ray.plan_y = old_planx * sinus + data->ray.plan_y * cosi;
}

void	left_right_movement(int nega, t_perso *perso)
{
	perso->dirx = -1 * nega * sin(perso->angle * M_PI / 180);
	perso->diry = -1 * nega * cos(perso->angle * M_PI / 180);
}

void	forward_backward_movement(int nega, t_perso *perso)
{
	if (perso->angle == 30 || perso->angle == 45 || perso->angle == 60 || perso->angle == 210
			||	perso->angle == 225 || perso->angle == 240)
	{
		perso->dirx = nega * cos(perso->angle * M_PI / 180 - 90) * -1;
		perso->diry = nega * sin(perso->angle * M_PI / 180 - 90) * -1;
	}
	else if (perso->angle == 120 || perso->angle == 135 || perso->angle == 150 ||
			perso->angle == 315 || perso->angle == 330 || perso->angle == 300)
	{
		perso->dirx = nega * cos(perso->angle * M_PI / 180 + 90) * -1;
		perso->diry = nega * sin(perso->angle * M_PI / 180 + 90) * -1;
	}
	else if ((perso->angle >= 0 && perso->angle < 60) || (perso->angle >= 165 &&
				perso->angle < 240)
			|| (perso->angle >= 330 && perso->angle < 360))
	{
		perso->dirx = -1 * nega * cos(perso->angle * M_PI / 180);
		perso->diry = -1 * nega * sin(perso->angle * M_PI / 180);
	}
	else
	{
		perso->dirx = nega * cos(perso->angle * M_PI / 180);
		perso->diry = nega * sin(perso->angle * M_PI / 180);
	}
}
