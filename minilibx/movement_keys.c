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

void	left_right_movement(int nega, t_perso *perso)
{
	if (perso->angle == 45 || perso->angle == 225 || perso->angle == 135 ||
			perso->angle == 315)
	{
		perso->dirx = nega * sin(perso->angle * M_PI / 180 + 90) * -1;
		perso->diry = nega * cos(perso->angle * M_PI / 180 + 90) * -1;
	}
	else if (perso->angle == 135 || perso->angle == 315)
	{
		perso->dirx = nega * sin(perso->angle * M_PI / 180 - 90) * -1;
		perso->diry = nega * cos(perso->angle * M_PI / 180 - 90) * -1;
	}
	else if ((perso->angle >= 0 && perso->angle < 60) || (perso->angle >= 165 &&
				perso->angle < 240)
			|| (perso->angle >= 330 && perso->angle < 360))
	{
		perso->dirx = nega * sin(perso->angle * M_PI / 180);
		perso->diry = nega * cos(perso->angle * M_PI / 180);
	}
	else
	{
		perso->dirx = -1 * nega * sin(perso->angle * M_PI / 180);
		perso->diry = -1 * nega * cos(perso->angle * M_PI / 180);
	}
}

void	forward_backward_movement(int nega, t_perso *perso)
{
	perso->dirx = nega * cos(perso->angle * M_PI / 180);
	perso->diry = nega * sin(perso->angle * M_PI / 180);
}
