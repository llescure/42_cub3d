#include "../include/struct_cub3d.h"
#include "../include/cub3d.h"

void	rotate_camera_left(t_ray *ray)
{
	double old_dirx;
	double old_planx;
	double cosi;
	double sinus;

	old_planx = ray->plan_x;
	old_dirx = ray->dir_x;
	cosi = cos(-15 * M_PI / 180);
	sinus = sin(-15 * M_PI / 180);
	ray->dir_x = ray->dir_x * cosi - ray->dir_y * sinus;
	ray->dir_y = old_dirx * sinus + ray->dir_y * cosi;
	ray->plan_x = ray->plan_x * cosi - ray->plan_y * sinus;
	ray->plan_y = old_planx * sinus + ray->plan_y * cosi;
}

void	rotate_camera_right(t_ray *ray)
{
	double old_dirx;
	double old_planx;
	double cosi;
	double sinus;

	old_planx = ray->plan_x;
	old_dirx = ray->dir_x;
	cosi = cos(15 * M_PI / 180);
	sinus = sin(15 * M_PI / 180);
	ray->dir_x = ray->dir_x * cosi - ray->dir_y * sinus;
	ray->dir_y = old_dirx * sinus + ray->dir_y * cosi;
	ray->plan_x = ray->plan_x * cosi - ray->plan_y * sinus;
	ray->plan_y = old_planx * sinus + ray->plan_y * cosi;
}

void	left_right_movement(int nega, t_data *data)
{
	if ((data->param.perso.angle >= 0 && data->param.perso.angle < 90) ||
			(data->param.perso.angle >= 180 && data->param.perso.angle < 270))
	{
		data->param.perso.dirx = nega * sin(data->param.perso.angle *
				M_PI / 180);
		data->param.perso.diry = nega * cos(data->param.perso.angle *
				M_PI / 180);
	}
	else
	{
		data->param.perso.dirx = -1 * nega * sin(data->param.perso.angle *
				M_PI / 180);
		data->param.perso.diry = -1 * nega * cos(data->param.perso.angle *
				M_PI / 180);
	}
}

void	forward_backward_movement(int nega, t_data *data)
{
	data->param.perso.dirx = nega * cos(data->param.perso.angle *
			M_PI / 180);
	data->param.perso.diry = nega * sin(data->param.perso.angle *
			M_PI / 180);
}
