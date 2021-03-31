#include "../include/struct_cub3D.h"
#include "../include/cub3D.h"
#include "../parsing/minilibx/mlx.h"
#include <math.h>

void		initialize_ray(t_ray *ray)
{
	ray->perpWallDist = 0;
	ray->lineHeight = 0;
	ray->drawStart = 0;
	ray->drawEnd = 0;
}
int raycasting(t_param *param, t_ray *ray)
{
	int osef = 250;
	int x;
	t_mlx mlx;
	t_colour color;

	x = 0;
	mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, param->resolution.axe_y, param->resolution.axe_x, "tu marches");
	mlx.img_ptr = mlx_new_image(mlx.mlx_ptr, param->resolution.axe_y, param->resolution.axe_x);
	mlx.img_data = mlx_get_data_addr(mlx.img_ptr, &osef, &osef, &osef);
//start the main loop
  while (x < param->resolution.axe_x)
  {
      //calculate ray position and direction
      ray->cameraX = 2 * x / (double)(param->resolution.axe_x) - 1; //x-coordinate in camera space
      ray->rayDirY = ray->dirY + ray->planY * ray->cameraX;
      ray->rayDirX = ray->dirX + ray->planX * ray->cameraX;

      //which box of the map we're in
      ray->mapY = (int)(ray->posY);
      ray->mapX = (int)(ray->posX);

      //length of ray from one x or y-side to next x or y-side
      ray->deltaDistY = sqrt(1 + (ray->rayDirX * ray->rayDirX) / (ray->rayDirY * ray->rayDirY));
      ray->deltaDistX = sqrt(1 + (ray->rayDirY * ray->rayDirY) / (ray->rayDirX * ray->rayDirX));

      ray->hit = 0; //was there a wall hit?

      //calculate step and initial sideDist
      if (ray->rayDirY < 0)
      {
        ray->stepY = -1;
        ray->sideDistY = (ray->posY - ray->mapY) * ray->deltaDistY;
      }
      else
      {
        ray->stepY = 1;
        ray->sideDistY = (ray->mapY + 1.0 - ray->posY) * ray->deltaDistY;
      }
      if (ray->rayDirX < 0)
      {
        ray->stepX = -1;
        ray->sideDistX = (ray->posX - ray->mapX) * ray->deltaDistX;
      }
      else
      {
        ray->stepX = 1;
        ray->sideDistX = (ray->mapX + 1.0 - ray->posX) * ray->deltaDistX;
      }
	  //perform DDA
	  while (ray->hit == 0)
	  {
		  //jump to next map square, OR in x-direction, OR in y-direction
		  if (ray->sideDistY < ray->sideDistX)
		  {
			  ray->sideDistY += ray->deltaDistY;
			  ray->mapY += ray->stepY;
			  ray->side = 0;
		  }
		  else
		  {
			  ray->sideDistX += ray->deltaDistX;
			  ray->mapX += ray->stepX;
			  ray->side = 1;
		  }
		  //Check if ray has hit a wall

		  if (param->map.tab_map[ray->mapY][ray->mapX] > 0)
		  		ray->hit = 1;
	 }
	 		print_ray(ray);
		  //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		  if (ray->side == 0)
		  		ray->perpWallDist = (ray->mapY - ray->posY + (1 - ray->stepY) / 2) / ray->rayDirY;
		  else
		  		ray->perpWallDist = (ray->mapX - ray->posX + (1 - ray->stepX)) / 2 / ray->rayDirX;
		  //Calculate height of line to draw on screen
		  ray->lineHeight = (int)(param->resolution.axe_x / ray->perpWallDist); // h = resolution maximal y
		  //calculate lowest and highest pixel to fill in current stripe
	      ray->drawStart = -ray->lineHeight / 2 + param->resolution.axe_y / 2;
	      if (ray->drawStart < 0)
		  		ray->drawStart = 0;
	      ray->drawEnd = ray->lineHeight / 2 + param->resolution.axe_y / 2;
	      if (ray->drawEnd >= param->resolution.axe_y)
		  		ray->drawEnd = param->resolution.axe_y - 1;
		  //choose wall color
		  if (param->map.tab_map[(int)ray->posY][(int)ray->posX] == 1)
		{
			color.red = 255;
			color.green = 0;
			color.blue = 0;
		}
		else if (param->map.tab_map[(int)ray->posY][(int)ray->posX] == 2)
		{
			color.red = 0;
			color.green = 255;
			color.blue = 0;
		}
		else if (param->map.tab_map[(int)ray->posY][(int)ray->posX] == 3)
		{
			color.red = 0;
			color.green = 0;
			color.blue = 255;
		}
		else if (param->map.tab_map[(int)ray->posY][(int)ray->posX] == 4)
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
/*	      switch(worldMap[mapY][mapX])
	      {
	        case 1:  color = RGB_Red;  break; //red
	        case 2:  color = RGB_Green;  break; //green
	        case 3:  color = RGB_Blue;   break; //blue
	        case 4:  color = RGB_White;  break; //white
	        default: color = RGB_Xellow; break; //yellow
		}*/
		display(x, ray->drawStart, ray->drawEnd, color, mlx.img_data, param->resolution.axe_y);
		x++;
	}
	mlx_clear_window ( mlx.mlx_ptr, mlx.win_ptr);
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

void init(t_param *param)
{
	t_ray ray;
	ray.posX = param->perso.position_x;
	ray.posY = param->perso.position_y;
	initialisation_orientation(param, &ray);
	initialize_ray(&ray);
	raycasting(param, &ray);
}
