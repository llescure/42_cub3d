#include "../include/cub3D.h"
#include "../include/struct_cub3D.h"

int		initialisation_orientation(t_param *param, t_ray *ray)
{
	if (param->perso.orientation == 'N')
	{
		ray->dirx = -1;
		ray->diry = 0;
		ray->planx = 0;
		ray->plany = 0.66;
	}
	if (param->perso.orientation == 'S')
	{
		ray->dirx = 1;
		ray->diry = 0;
		ray->planx = 0;
		ray->plany = -0.66;
	}
	if (param->perso.orientation == 'W')
	{
		ray->dirx = 0;
		ray->diry = -1;
		ray->planx = -0.66;
		ray->plany = 0;
	}
	if (param->perso.orientation == 'E')
	{
		ray->dirx = 0;
		ray->diry = 1;
		ray->planx = 0.66;
		ray->plany = 0;
	}
	return (0);
}

int print_ray(t_ray *ray)
{
	printf("posx = %f\n", ray->posx);
	printf("posy = %f\n", ray->posy);
	printf("dirx = %f\n", ray->dirx);
	printf("diry = %f\n", ray->diry);
	printf("planx = %f\n", ray->planx);
	printf("plany = %f\n", ray->plany);
	return (0);
}

int raycasting(t_param *param, t_ray *ray)
{
	ray->posx = param->perso.position_x;
	ray->posy = param->perso.position_y;
	initialisation_orientation(param, ray);
	print_ray(ray);
/*	while (ray->posx < param->map.max_length)
	{

	}*/
	return (0);
}
