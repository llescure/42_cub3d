#include "../include/struct_cub3d.h"
#include "../include/cub3d.h"

int		initialisation_orientation(t_param *param, t_ray *ray)
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
	return (0);
}

int raycasting(t_data *data, t_ray *ray)
{
	int x = 0;

	while(x < data->param.resolution.axe_x)
	{
		// printf("resolution x = %i, resolution y = %i\n", param->resolution.axe_x, param->resolution.axe_y);
		ray->camera_x = 2 * x / (double)data->param.resolution.axe_x - 1; //x-coordinate in camera space // camerax
		// printf("cameraX = %f\n", ray->cameraX);
		ray->ray_diry = ray->dir_x + ray->plan_x * ray->camera_x; //raydirx
		ray->ray_dirx = ray->dir_y + ray->plan_y * ray->camera_x;//raydiry
		// printf("raydirX = %f, rayDirY = %f\n", ray->rayDirX, ray->rayDirY);
		ray->map_x = (int)ray->pos_x;//mapx
		ray->map_y = (int)ray->pos_y;//mapy
		ray->delta_distx = sqrt(1 + (ray->ray_diry * ray->ray_diry) /
				(ray->ray_dirx * ray->ray_dirx));
		ray->delta_disty = sqrt(1 + (ray->ray_dirx * ray->ray_dirx) /
				(ray->ray_diry * ray->ray_diry));
		// printf("raydirX = %f, rayDirY = %f\n", ray->rayDirX, ray->rayDirY);
		ray->hit = 0; //was there a wall hit?
		//printf("ray->dir_x = %f\n", ray->dir_x);
		if(ray->ray_dirx < 0)
		{
			ray->step_x = -1;
			ray->side_distx = (ray->pos_x - ray->map_x) * ray->delta_distx;
		}
		else
		{
			ray->step_x = 1;
			ray->side_distx = (ray->map_x + 1.0 - ray->pos_x) *
				ray->delta_distx;
		}
		if(ray->ray_diry < 0)
		{
			ray->step_y = -1;
			ray->side_disty = (ray->pos_y - ray->map_y) * ray->delta_disty;
		}
		else
		{
			ray->step_y = 1;
			ray->side_disty = (ray->map_y + 1.0 - ray->pos_y) *
				ray->delta_disty;
		}
		// printf("stepX = %d, stepY= %d, posX = %f, posY = %f, mapX = %d, mapY = %d, deltaDistX = %f, deltaDistY = %f\n", ray->stepX, ray->stepY, ray->posX, ray->posY, ray->mapX, ray->mapY, ray->deltaDistX, ray->deltaDistY);
// ray->side = 0;
		// printf("sideDistX = %f, sideDistY = %f, mapX = %d, mapY = %d, deltaDistX = %f, deltaDistY = %f, stepX = %d, stepY = %d, side = %i, hit = %i\n", ray->sideDistX, ray->sideDistY, ray->mapX, ray->mapY, ray->deltaDistX, ray->deltaDistY, ray->stepX, ray->stepY, ray->side, ray->hit);

		while (ray->hit == 0)
		{
			if(ray->side_distx < ray->side_disty)
			{
				ray->side_distx += ray->delta_distx;
				ray->map_x += ray->step_x;
				ray->side = 0;
				data->texture.shade = 0.75;
			}
			else
			{
				ray->side_disty += ray->delta_disty;
				ray->map_y += ray->step_y;
				ray->side = 1;
				data->texture.shade = 1;
			}
			if(data->param.map.tab_map[ray->map_x][ray->map_y] == '1')
				ray->hit = 1;
			else if(data->param.map.tab_map[ray->map_x][ray->map_y] == '2')
				ray->hit = 2;
		}
		// printf("hit = %i\n", ray->hit);
		// printf("sideDistX = %f, sideDistY = %f, mapX = %d, mapY = %d, deltaDistX = %f, deltaDistY = %f, stepX = %d, stepY = %d, side = %i, hit = %i\n", ray->sideDistX, ray->sideDistY, ray->mapX, ray->mapY, ray->deltaDistX, ray->deltaDistY, ray->stepX, ray->stepY, ray->side, ray->hit);
		// printf("hit = %i\n", ray->hit);
		if(ray->side == 0)
			ray->perp_wall_dist = (ray->map_x - ray->pos_x + (1 - ray->step_x)
					/ 2) / ray->ray_dirx;
		else
			ray->perp_wall_dist = (ray->map_y - ray->pos_y + (1 - ray->step_y)
					/ 2) / ray->ray_diry;
		if (ray->perp_wall_dist == 0)
			ray->perp_wall_dist = 0.1;
		// if (ray->perpWallDist == 0)
		// 	ray->perpWallDist = 10;
		ray->line_height = (int)(data->param.resolution.axe_y /
				ray->perp_wall_dist);
		ray->draw_start = -ray->line_height / 2 +
			data->param.resolution.axe_y / 2;
		if(ray->draw_start < 0)
			ray->draw_start = 0;
		ray->draw_end = ray->line_height / 2 + data->param.resolution.axe_y / 2;
		if(ray->draw_end >= data->param.resolution.axe_y)
			ray->draw_end = data->param.resolution.axe_y - 1;
		// printf("lineHeight = %d, drawStart = %d, drawEnd = %d\n\n", ray->lineHeight, ray->drawStart, ray->drawEnd);
		// print_ray(ray);
		draw_column(ray->draw_start, ray->draw_end, x, data);
		draw_floor(ray->draw_end, data->param.resolution.axe_y, x, data);
		draw_ceiling(0, ray->draw_start, x, data);
		x++;
	}
	return (0);
}

int print_ray(t_ray *ray)
{
	printf("posx = %f\n", ray->pos_y);
	printf("posy = %f\n", ray->pos_x);
	printf("dirx = %f\n", ray->dir_y);
	printf("diry = %f\n", ray->dir_x);
	printf("planx = %f\n", ray->plan_y);
	printf("plany = %f\n", ray->plan_x);
	printf("mapx = %i\n", ray->map_y);
	printf("mapy = %i\n", ray->map_x);
	printf("raydirY = %f\n", ray->ray_diry);
	printf("raydirX = %f\n", ray->ray_dirx);
	printf("stepY = %i\n", ray->step_x);
	printf("stepX = %i\n", ray->step_y);
	printf("perpwalldist = %f\n", ray->perp_wall_dist);
	printf("lineheight= %i\n", ray->line_height);
	printf("drawstart = %i\n", ray->draw_start);
	printf("drawend = %i\n", ray->draw_end);
	return (0);
}
