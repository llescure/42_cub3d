#include <math.h>
#include "../parsing/minilibx/mlx.h"

typedef struct	s_mlx
{
	int key;
	void *mlx_ptr;
	void *win_ptr;
	void *img_ptr;
	char *img_data;
}				t_mlx;

typedef struct s_color
{
	int r;
	int g;
	int b;
}	t_color;

void putPixel(unsigned char r, unsigned char g, unsigned char b, char *img_data, int x, int y, int res)
{
	img_data[(x + y * res) * 4] = (char)b;
	img_data[(x + y * res) * 4 + 1] = (char)g;
	img_data[(x + y * res) * 4 + 2] = (char)r;
	img_data[(x + y * res) * 4 + 3] = 0;
}

void    display(int x, double haut, double bas, t_color color, char *img_data, int res)
{
	(void)color;
	while (bas < haut)
	{
		//putPixel(255, 255, 255, img_data, x, bas, res);

		 putPixel(color.r, color.g, color.b, img_data, x, bas, res);
		bas++;
	}
}



int main()
{
	int worldMap[24][24]=
	{
	  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,0,0,0,0,0,2,2,2,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,3,0,0,0,3,0,0,0,1},
	  {1,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,0,0,0,0,0,2,2,0,2,2,0,0,0,0,3,0,3,0,3,0,0,0,1},
	  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,4,0,0,0,0,5,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,4,0,4,0,0,0,0,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,4,0,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,4,4,4,4,4,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	  {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
	};
	int osef = 250;
	t_mlx mlx;
	mlx.mlx_ptr = mlx_init();
	mlx.win_ptr = mlx_new_window(mlx.mlx_ptr, 1080, 1080, "tu marches");
	mlx.img_ptr = mlx_new_image(mlx.mlx_ptr, 1080, 1080);
	mlx.img_data = mlx_get_data_addr(mlx.img_ptr, &osef, &osef, &osef);
	double posX = 22, posY = 10;  //x and y start position
	double dirX = -1, dirY = 0; //initial direction vector
	double planeX = 0, planeY = 0.66; //the 2d raycaster version of camera plane
//	double time = 0; //time of current frame
//	double oldTime = 0; //time of previous frame
//start the main loop
  while (1)
  {
    for(int x = 0; x < 600; x++) // w = resolution maximmal de x
    {

      //calculate ray position and direction
      double cameraX = 2*x/(double)(1080)-1; //x-coordinate in camera space
      double rayDirX = dirX + planeX*cameraX;
      double rayDirY = dirY + planeY*cameraX;

      //which box of the map we're in
      int mapX = (int)(posX);
      int mapY = (int)(posY);

      //length of ray from current position to next x or y-side
      double sideDistX;
      double sideDistY;

      //length of ray from one x or y-side to next x or y-side
      double deltaDistX = sqrt(1 + (rayDirY * rayDirY) / (rayDirX * rayDirX));
      double deltaDistY = sqrt(1 + (rayDirX * rayDirX) / (rayDirY * rayDirY));
      double perpWallDist;

      //what direction to step in x or y-direction (either +1 or -1)
      int stepX;
      int stepY;

      int hit = 0; //was there a wall hit?
      int side; //was a NS or a EW wall hit?

      //calculate step and initial sideDist
      if (rayDirX < 0)
      {
        stepX = -1;
        sideDistX = (posX - mapX) * deltaDistX;
      }
      else
      {
        stepX = 1;
        sideDistX = (mapX + 1.0 - posX) * deltaDistX;
      }
      if (rayDirY < 0)
      {
        stepY = -1;
        sideDistY = (posY - mapY) * deltaDistY;
      }
      else
      {
        stepY = 1;
        sideDistY = (mapY + 1.0 - posY) * deltaDistY;
      }
	  //perform DDA
	  while (hit == 0)
	  {
		  //jump to next map square, OR in x-direction, OR in y-direction
		  if (sideDistX < sideDistY)
		  {
			  sideDistX += deltaDistX;
			  mapX += stepX;
			  side = 0;
		  }
		  else
		  {
			  sideDistY += deltaDistY;
			  mapY += stepY;
			  side = 1;
		  }
		  //Check if ray has hit a wall
		  if (worldMap[mapX][mapY] > 0)
		  		hit = 1;
	}
		  //Calculate distance projected on camera direction (Euclidean distance will give fisheye effect!)
		  if (side == 0)
		  		perpWallDist = (mapX - posX + (1 - stepX) / 2) / rayDirX;
		  else
		  		perpWallDist = (mapY - posY + (1 - stepY) / 2) / rayDirY;
		  //Calculate height of line to draw on screen
		  int lineHeight = (int)(1080 / perpWallDist); // h = resolution maximal y
		  //calculate lowest and highest pixel to fill in current stripe
	      int drawStart = -lineHeight / 2 + 1080 / 2;
	      if(drawStart < 0)drawStart = 0;
	      int drawEnd = lineHeight / 2 + 1080 / 2;
	      if(drawEnd >= 1080)drawEnd = 1080 - 1;
		  //choose wall color
		  t_color color;
		  if (worldMap[(int)posX][(int)posY] == 1)
		{
			color.r = 255;
			color.g = 0;
			color.b = 0;
		}
		else if (worldMap[(int)posX][(int)posY] == 2)
		{
			color.r = 0;
			color.g = 255;
			color.b = 0;
		}
		else if (worldMap[(int)posX][(int)posY] == 3)
		{
			color.r = 0;
			color.g = 0;
			color.b = 255;
		}
		else if (worldMap[(int)posX][(int)posY] == 4)
		{
			color.r = 255;
			color.g = 255;
			color.b = 255;
		}
		else
		{
			color.r = 127;
			color.g = 127;
			color.b = 127;
		}
/*	      switch(worldMap[mapX][mapY])
	      {
	        case 1:  color = RGB_Red;  break; //red
	        case 2:  color = RGB_Green;  break; //green
	        case 3:  color = RGB_Blue;   break; //blue
	        case 4:  color = RGB_White;  break; //white
	        default: color = RGB_Yellow; break; //yellow
		}*/
		printf("drawend = %i, drawstart = %i\n", drawEnd, drawStart);
		display(x, drawEnd, drawStart, color, mlx.img_data, 1080);
	}
	mlx_clear_window ( mlx.mlx_ptr, mlx.win_ptr );
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, mlx.img_ptr, 0, 0);
	mlx_loop(mlx.mlx_ptr);
	return (0);
	      //give x and y sides different brightness
}
}
