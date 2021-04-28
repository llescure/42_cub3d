#include "../include/struct_cub3d.h"
#include "../include/cub3d.h"

void	initialize_data_for_raycasting(t_ray *ray)
{
	if (ray->ray_dirx < 0)
	{
		ray->step_x = -1;
		ray->side_distx = (ray->pos_x - ray->map_x) * ray->delta_distx;
	}
	else
	{
		ray->step_x = 1;
		ray->side_distx = (ray->map_x + 1.0 - ray->pos_x) * ray->delta_distx;
	}
	if (ray->ray_diry < 0)
	{
		ray->step_y = -1;
		ray->side_disty = (ray->pos_y - ray->map_y) * ray->delta_disty;
	}
	else
	{
		ray->step_y = 1;
		ray->side_disty = (ray->map_y + 1.0 - ray->pos_y) * ray->delta_disty;
	}
}

void	wall_collision(t_data *data, t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->side_distx < ray->side_disty)
		{
			ray->side_distx += ray->delta_distx;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->side_disty += ray->delta_disty;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (data->param.map.tab_map[ray->map_x][ray->map_y] == '1')
			ray->hit = 1;
	}
}

void	display_raycasting(t_data *data, t_ray *ray, int x)
{
	int i;

	i = 0;
	if (ray->side == 0)
		ray->perp_wall_dist = (ray->map_x - ray->pos_x + (1 - ray->step_x)
				/ 2) / ray->ray_dirx;
	else
		ray->perp_wall_dist = (ray->map_y - ray->pos_y + (1 - ray->step_y)
				/ 2) / ray->ray_diry;
	if (ray->perp_wall_dist == 0)
		ray->perp_wall_dist = 0.1;
	ray->line_height = (int)(data->param.resolution.axe_y /
			ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 +
		data->param.resolution.axe_y / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + data->param.resolution.axe_y / 2;
	if (ray->draw_end >= data->param.resolution.axe_y)
		ray->draw_end = data->param.resolution.axe_y - 1;
	data->texture.shade = shadow_texture(ray->perp_wall_dist);
	draw_floor(ray->draw_end, data->param.resolution.axe_y, x, data);
	draw_ceiling(0, ray->draw_start, x, data);
	draw_texture_walls(data, x);
	while (i < data->param.nb_sprites)
	{
		data->tab_sprite[i].z_buffer[x] = data->ray.perp_wall_dist;
		i++;
	}
}

void	raycasting(t_data *data, t_ray *ray)
{
	int x;

	x = 0;
	while (x < data->param.resolution.axe_x)
	{
		ray->camera_x = 2 * x / (double)data->param.resolution.axe_x - 1;
		ray->ray_diry = ray->dir_x + ray->plan_x * ray->camera_x;
		ray->ray_dirx = ray->dir_y + ray->plan_y * ray->camera_x;
		ray->map_x = (int)ray->pos_x;
		ray->map_y = (int)ray->pos_y;
		ray->delta_distx = sqrt(1 + (ray->ray_diry * ray->ray_diry) /
				(ray->ray_dirx * ray->ray_dirx));
		ray->delta_disty = sqrt(1 + (ray->ray_dirx * ray->ray_dirx) /
				(ray->ray_diry * ray->ray_diry));
		ray->hit = 0;
		initialize_data_for_raycasting(ray);
		wall_collision(data, ray);
		display_raycasting(data, ray, x);
		x++;
	}
	ft_sprites(data);
}
