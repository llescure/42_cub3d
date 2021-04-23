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
	cosi = cos(2.5 * M_PI / 180);
	sinus = sin(2.5 * M_PI / 180);
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
	cosi = cos(-2.5 * M_PI / 180);
	sinus = sin(-2.5 * M_PI / 180);
	data->ray.dir_x = data->ray.dir_x * cosi - data->ray.dir_y * sinus;
	data->ray.dir_y = old_dirx * sinus + data->ray.dir_y * cosi;
	data->ray.plan_x = data->ray.plan_x * cosi - data->ray.plan_y * sinus;
	data->ray.plan_y = old_planx * sinus + data->ray.plan_y * cosi;
}

void	left_right_movement(int nega, t_perso *perso)
{
		perso->dirx = nega * 0;
		perso->diry = nega * -1;
}

void	forward_backward_movement(int nega, t_perso *perso)
{
		perso->dirx = nega * -1;
		perso->diry = nega * 0;
}
