#include "../include/struct_cub3d.h"
#include "../include/cub3d.h"

void	initialisation_orientation(t_param *param, t_ray *ray)
{
	if (param->perso.orientation == 'N' || param->perso.orientation == 'S')
		orientation_north_south(param, ray);
	if (param->perso.orientation == 'W')
	{
		ray->dir_y = 0;
		ray->dir_x = -1;
		ray->plan_y = -0.66;
		ray->plan_x = 0;
		param->perso.angle = 180;
	}
	if (param->perso.orientation == 'E')
	{
		ray->dir_y = 0;
		ray->dir_x = 1;
		ray->plan_y = 0.66;
		ray->plan_x = 0;
		param->perso.angle = 0;
	}
}

void	orientation_north_south(t_param *param, t_ray *ray)
{
	if (param->perso.orientation == 'N')
	{
		ray->dir_y = -1;
		ray->dir_x = 0;
		ray->plan_y = 0;
		ray->plan_x = -0.66;
		param->perso.angle = 270;
	}
	if (param->perso.orientation == 'S')
	{
		ray->dir_y = 1;
		ray->dir_x = 0;
		ray->plan_y = 0;
		ray->plan_x = 0.66;
		param->perso.angle = 90;
	}
}
