#include "../include/struct_cub3D.h"
#include "../include/cub3D.h"

void putPixel(unsigned char r, unsigned char g, unsigned char b, char *img_data, int x, int y, int res)
{
	img_data[(x + y * res) * 4] = (char)b;
	img_data[(x + y * res) * 4 + 1] = (char)g;
	img_data[(x + y * res) * 4 + 2] = (char)r;
	img_data[(x + y * res) * 4 + 3] = 0;
}

void    display(int x, double haut, double bas, t_param param->colour color, char *img_data, int res, t_param *param)
{
//	(void)color;
	while (bas < haut)
	{
		//putPixel(255, 255, 255, img_data, x, bas, res);

		 putPixel(param.colour.red, param.colour.green, param.colour.blue, img_data, x, bas, res);
		bas++;
	}
}
