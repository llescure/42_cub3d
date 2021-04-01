#include "../include/struct_cub3D.h"
#include "../include/cub3D.h"
#include "../parsing/minilibx/mlx.h"
#include <math.h>

double	val_abs(double t)
{
	if (t < 0)
		t = -t;
	return (t);
}

int		initialisation_orientation(t_param *param, t_ray *ray)
{
	if (param->perso.orientation == 'N')
	{
		ray->dirY = -1;
		ray->dirX = 0;
		ray->planY = 0;
		ray->planX = 0.66;
	}
	if (param->perso.orientation == 'S')
	{
		ray->dirY = 1;
		ray->dirX = 0;
		ray->planY = 0;
		ray->planX = -0.66;
	}
	if (param->perso.orientation == 'W')
	{
		ray->dirY = 0;
		ray->dirX = -1;
		ray->planY = -0.66;
		ray->planX = 0;
	}
	if (param->perso.orientation == 'E')
	{
		ray->dirY = 0;
		ray->dirX = 1;
		ray->planY = 0.66;
		ray->planX = 0;
	}
	return (0);
}

int raycasting(t_param *param, t_ray *ray)
{
	int x = 0;
	t_colour color;
	t_mlx mlx;
	int osef = 250;

	mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, param->resolution.axe_x, param->resolution.axe_y, "allez kiki");
	mlx.img_ptr = mlx_new_image(mlx.mlx_ptr, param->resolution.axe_x, param->resolution.axe_y);
	mlx.img_data = mlx_get_data_addr(mlx.img_ptr, &osef, &osef, &osef);

	while(x < param->resolution.axe_x)
	{
		// printf("resolution x = %i, resolution y = %i\n", param->resolution.axe_x, param->resolution.axe_y);
		ray->cameraX = 2 * x / (double)param->resolution.axe_x - 1; //x-coordinate in camera space // camerax
		// printf("cameraX = %f\n", ray->cameraX);
		ray->rayDirY = ray->dirX + ray->planX * ray->cameraX; //raydirx
		ray->rayDirX = ray->dirY + ray->planY * ray->cameraX;//raydiry
		// printf("raydirX = %f, rayDirY = %f\n", ray->rayDirX, ray->rayDirY);
		ray->mapX = (int)ray->posX;//mapx
		ray->mapY = (int)ray->posY;//mapy
		ray->deltaDistX = sqrt(1 + (ray->rayDirY * ray->rayDirY) / (ray->rayDirX * ray->rayDirX));
		ray->deltaDistY = sqrt(1 + (ray->rayDirX * ray->rayDirX) / (ray->rayDirY * ray->rayDirY));
		// printf("raydirX = %f, rayDirY = %f\n", ray->rayDirX, ray->rayDirY);
		ray->hit = 0; //was there a wall hit?
		if(ray->rayDirX < 0)
		{
			ray->stepX = -1;
			ray->sideDistX = (ray->posX - ray->mapX) * ray->deltaDistX;
		}
		else
		{
			ray->stepX = 1;
			ray->sideDistX = (ray->mapX + 1.0 - ray->posX) * ray->deltaDistX;
		}
		if(ray->rayDirY < 0)
		{
			ray->stepY = -1;
			ray->sideDistY = (ray->posY - ray->mapY) * ray->deltaDistY;
		}
		else
		{
			ray->stepY = 1;
			ray->sideDistY = (ray->mapY + 1.0 - ray->posY) * ray->deltaDistY;
		}
		// printf("stepX = %d, stepY= %d, posX = %f, posY = %f, mapX = %d, mapY = %d, deltaDistX = %f, deltaDistY = %f\n", ray->stepX, ray->stepY, ray->posX, ray->posY, ray->mapX, ray->mapY, ray->deltaDistX, ray->deltaDistY);
// ray->side = 0;
		// printf("sideDistX = %f, sideDistY = %f, mapX = %d, mapY = %d, deltaDistX = %f, deltaDistY = %f, stepX = %d, stepY = %d, side = %i, hit = %i\n", ray->sideDistX, ray->sideDistY, ray->mapX, ray->mapY, ray->deltaDistX, ray->deltaDistY, ray->stepX, ray->stepY, ray->side, ray->hit);

		while (ray->hit == 0)
		{
			if(ray->sideDistX < ray->sideDistY)
			{
				ray->sideDistX += ray->deltaDistX;
				ray->mapX += ray->stepX;
				ray->side = 0;
			}
			else
			{
				ray->sideDistY += ray->deltaDistY;
				ray->mapY += ray->stepY;
				ray->side = 1;
			}
			if(param->map.tab_map[ray->mapX][ray->mapY] > '0')
				ray->hit = 1;
		}
		// printf("hit = %i\n", ray->hit);
		// printf("sideDistX = %f, sideDistY = %f, mapX = %d, mapY = %d, deltaDistX = %f, deltaDistY = %f, stepX = %d, stepY = %d, side = %i, hit = %i\n", ray->sideDistX, ray->sideDistY, ray->mapX, ray->mapY, ray->deltaDistX, ray->deltaDistY, ray->stepX, ray->stepY, ray->side, ray->hit);
		// printf("hit = %i\n", ray->hit);
		if(ray->side == 0)
			ray->perpWallDist = (ray->mapX - ray->posX + (1 - ray->stepX) / 2) / ray->rayDirX;
		else
			ray->perpWallDist = (ray->mapY - ray->posY + (1 - ray->stepY) / 2) / ray->rayDirY;
		if (ray->perpWallDist == 0)
			ray->perpWallDist = 0.1;
		// if (ray->perpWallDist == 0)
		// 	ray->perpWallDist = 10;
		ray->lineHeight = (int)(param->resolution.axe_y / ray->perpWallDist);
		ray->drawStart = -ray->lineHeight / 2 + param->resolution.axe_y / 2;
		if(ray->drawStart < 0)
			ray->drawStart = 0;
		ray->drawEnd = ray->lineHeight / 2 + param->resolution.axe_y / 2;
		if(ray->drawEnd >= param->resolution.axe_y)
			ray->drawEnd = param->resolution.axe_y - 1;
		// printf("lineHeight = %d, drawStart = %d, drawEnd = %d\n\n", ray->lineHeight, ray->drawStart, ray->drawEnd);
		// 	exit (0);
		if (param->map.tab_map[(int)ray->posX][(int)ray->posY] == '1')
		{
			color.red = 255;
			color.green = 0;
			color.blue = 0;
		}
		else if (param->map.tab_map[(int)ray->posX][(int)ray->posY] == '2')
		{
			color.red = 0;
			color.green = 255;
			color.blue = 0;
		}
		else if (param->map.tab_map[(int)ray->posX][(int)ray->posY] == '3')
		{
			color.red = 0;
			color.green = 0;
			color.blue = 255;
		}
		else if (param->map.tab_map[(int)ray->posX][(int)ray->posY] == '4')
		{
			color.red = 255;
			color.green = 255;
			color.blue = 255;
		}
		else
		{
			color.red = 127;
			color.green = 127;
			color.blue = 127;
		}
		// print_ray(ray);
		display(x, ray->drawEnd, ray->drawStart, color, mlx.img_data, param->resolution.axe_x);
// if (x == 200)
// 	exit(0);
		x++;
	}
	mlx_clear_window (mlx.mlx_ptr, mlx.win_ptr );
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, mlx.img_ptr, 0, 0);
	mlx_loop(mlx.mlx_ptr);
	return (0);
}

int print_ray(t_ray *ray)
{
	printf("posx = %f\n", ray->posY);
	printf("posy = %f\n", ray->posX);
	printf("dirx = %f\n", ray->dirY);
	printf("diry = %f\n", ray->dirX);
	printf("planx = %f\n", ray->planY);
	printf("plany = %f\n", ray->planX);
	printf("mapx = %i\n", ray->mapY);
	printf("mapy = %i\n", ray->mapX);
	printf("raydirY = %f\n", ray->rayDirY);
	printf("raydirX = %f\n", ray->rayDirX);
	printf("stepY = %i\n", ray->stepX);
	printf("stepX = %i\n", ray->stepY);
	printf("perpwalldist = %f\n", ray->perpWallDist);
	printf("lineheight= %i\n", ray->lineHeight);
	printf("drawstart = %i\n", ray->drawStart);
	printf("drawend = %i\n", ray->drawEnd);
	return (0);
}

/*char	*ft_windowname(char *file)
{
	int		i;
	char	*ret;

	i = 0;
	while (file[i + 4])
		i++;
	if (!(ret = malloc(sizeof(char) * i + 1)))
		return (NULL);
	ret[i] = '\0';
	i = 0;
	while (file[i + 4])
	{
		ret[i] = file[i];
		i++;
	}
	return (ret);
}*/

void init(t_param *param)
{
	t_ray ray;
	ray.posX = (double)param->perso.position_y + 0.5; // + 0.5 pour corriger position sur le bloc
	ray.posY = (double)param->perso.position_x + 0.5;
	initialisation_orientation(param, &ray);
	raycasting(param, &ray);
}
