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
	printf("raydirx = %f\n", ray->raydirx);
	printf("raydiry = %f\n", ray->raydiry);
	printf("perpwalldist = %f\n", ray->perpwalldist);
	printf("lineheight= %i\n", ray->lineheight);
	printf("drawstart = %i\n", ray->drawstart);
	printf("drawend = %i\n", ray->drawend);
	return (0);
}

int raycasting(t_param *param, t_ray *ray)
{
	int x;
	int w;
	int color;
//	double time = 0; //time of current frame
//	double oldTime = 0; //time of previous frame

	x = -1;
	w = param->map.max_length;
	ray->posx = param->perso.position_x;
	ray->posy = param->perso.position_y;
	initialisation_orientation(param, ray);
	print_ray(ray);

	while (++x < w)
	{
		ray->camerax = 2 * x / w - 1;
		ray->raydirx = ray->dirx + ray->planx * ray->camerax;
		ray->raydiry = ray->diry + ray->plany * ray->camerax;

		ray->mapx = (int)(ray->posx);
		ray->mapy = (int)(ray->posy);
		if ((int)(ray->raydirx) == 0)
			ray->deltadistx = 0;
		else
			ray->deltadistx = abs(1 / (int)(ray->raydirx));
		if ((int)(ray->raydiry) == 0)
			ray->deltadisty = 0;
		else
			ray->deltadisty = abs(1 / (int)(ray->raydiry));
		ray->hit = 0;
		if (ray->raydirx < 0)
		{
			ray->stepx = -1;
			ray->sidedistx = (ray->posx - ray->mapx) * ray->deltadistx;
		}
		else
		{
			ray->stepx = 1;
			ray->sidedistx = (ray->mapx + 1.0 - ray->posx) * ray->deltadistx;
		}
		if (ray->raydiry < 0)
		{
			ray->stepy = -1;
			ray->sidedisty = (ray->posy - ray->mapy) * ray->deltadisty;
		}
		else
		{
			ray->stepy = 1;
			ray->sidedisty = (ray->mapy + 1.0 - ray->posy) * ray->deltadisty;
		}
		while (ray->hit == 0)
		{
			//jump to next map square, OR in x-direction, OR in y-direction
			if (ray->sidedistx < ray->sidedisty)
			{
				ray->sidedistx += ray->deltadistx;
				ray->mapx += ray->stepx;
				ray->side = 0;
			}
			else
			{
				ray->sidedisty += ray->deltadisty;
				ray->mapy += ray->stepy;
				ray->side = 1;
			}
			if (param->map.map[ray->mapy][ray->mapx] != '0')
				ray->hit = 1;
		}
		if (ray->side == 0)
			ray->perpwalldist = (ray->mapx - ray->posx + (1 - ray->stepx) / 2) / ray->raydirx;
		else
			ray->perpwalldist = (ray->mapy - ray->posy + (1 - ray->stepy) / 2) / ray->raydiry;

		//Calculate height of line to draw on screen
		ray->lineheight = (int)(param->map.max_length / ray->perpwalldist);

		ray->drawstart = -ray->lineheight / 2 + param->map.max_length / 2;
		if (ray->drawstart < 0)
			ray->drawstart = 0;
		ray->drawend = ray->lineheight / 2 + param->map.max_length / 2;
		if (ray->drawend >= param->map.max_length)
			ray->drawend = param->map.max_length - 1;
		color = BLUE_PIXEL;

		//give x and y sides different brightness
		if(ray->side == 1)
			color = color / 2;
		print_ray(ray);
		//draw the pixels of the stripe as a vertical line
		draw_square(ray->drawstart, ray->drawend, data, color); // C'EST ICI QUE T'INTERVIENS LEY
		//timing for input and FPS counter
		oldtime = time;
		time = getTicks(); // ???
		double frameTime = (time - oldTime) / 1000.0; //frameTime is the time this frame has taken, in seconds
		print(1.0 / frameTime); //FPS counter
		redraw();
		cls();

		//speed modifiers
		double moveSpeed = frameTime * 5.0; //the constant value is in squares/second
		double rotSpeed = frameTime * 3.0; //the constant value is in radians/second
		readKeys();
		//move forward if no wall in front of you
		if(keyDown(SDLK_UP))
		{
			if(param->map.map[int(ray->posx + ray->dirx * moveSpeed)][int(ray->posy)] == false)
				ray->posx += ray->dirx * moveSpeed;
			if(param->map.map[int(ray->posx)][int(ray->posy + ray->diry * moveSpeed)] == false)
				ray->posy += ray->diry * moveSpeed;
		}
		//move backwards if no wall behind you
		if(keyDown(SDLK_DOWN))
		{
			if(param->map.map[int(ray->posx - ray->dirx * moveSpeed)][int(ray->posy)] == false)
				ray->posx -= ray->dirx * moveSpeed;
			if(param->map.map[int(ray->posx)][int(ray->posy - ray->diry * moveSpeed)] == false)
				ray->posy -= ray->diry * moveSpeed;
		}
		//rotate to the right
		if(keyDown(SDLK_RIGHT))
		{
			//both camera direction and camera plane must be rotated
			double oldDirX = ray->dirx;
			ray->dirx = ray->dirx * cos(-rotSpeed) - ray->diry * sin(-rotSpeed);
			ray->diry = oldDirX * sin(-rotSpeed) + ray->diry * cos(-rotSpeed);
			double oldPlaneX = ray->planex;
			ray->planex = ray->planex * cos(-rotSpeed) - ray->planey * sin(-rotSpeed);
			ray->planey = oldPlaneX * sin(-rotSpeed) + ray->planey * cos(-rotSpeed);
		}
		//rotate to the left
		if(keyDown(SDLK_LEFT))
		{
			//both camera direction and camera plane must be rotated
			double oldDirX = ray->dirx;
			ray->dirx = ray->dirx * cos(rotSpeed) - ray->diry * sin(rotSpeed);
			ray->diry = oldDirX * sin(rotSpeed) + ray->diry * cos(rotSpeed);
			double oldPlaneX = ray->planex;
			ray->planex = ray->planex * cos(rotSpeed) - ray->planey * sin(rotSpeed);
			ray->planey = oldPlaneX * sin(rotSpeed) + ray->planey * cos(rotSpeed);
		}
*/	}
	return (0);
}
