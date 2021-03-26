#include "../include/struct_cub3D.h"
#include "../include/cub3D.h"
#include <math.h>
#define PI 3.1415926535
#define P2 PI/2
#define P3 3 * PI/2
#define D 0.0174533 // 1 degree in radians

// C'EST QUOI PA PUTAIN

void buttons(unsigned char key, double pa, double px, double py, double pdx, double pdy)
{
	if (key == 'a')
	{
		pa = pa - 0.1;
		if (pa < 0)
		{
			pa += 2 * PI;
			pdx = cos(pa) * 5;
			pdy = sin(pa) * 5;
		}
	}
	if (key == 'd')
	{
		pa = pa + 0.1;
		if (pa > 2 * PI)
		{
			pa -= 2 * PI;
			pdx = cos(pa) * 5;
			pdy = sin(pa) * 5;
		}
	}
	if (key == 'w')
	{
		px += pdx;
		py += pdy;
	}
	if (key == 's')
	{
		px -= pdx;
		py -= pdy;
	}
}

double		distance(double ax, double ay, double bx, double by, double ra)
{
	return (cos(ra * PI / 180.0)) * (bx - ax) - (sin(ra * PI / 180.0)) * (by - ay);
//	return (sqrt((bx - ax ) * (bx - ax) + (by - ay) * (by - ay)));
}

void drawrays3D(double pa, double px, double py, t_param *param)
{
	int r;
	int mx;
	int my;
	int mp;
	int dof;
	int size_block = 64;
	double rx;
	double ry;
	double ra;
	double xo;
	double yo;
	double Tan;
	double distH;
	double hx = px;
	double hy = py;
	double distV;
	double vx = px;
	double vy = py;

	ra = fixAngle(pa + 30);
	r = 0; // number of rays
	while (r < 10) // nombre de rayons qu'il y aura, si >1 liberer le morceau de code
	{
		//CHECK VERTICAL LINES
		dof = 0;
		distV = 100000;
		Tan = tan(ra * PI / 180.0);
		if (cos(ra * PI / 180.0) > 0.001)
		{
			rx = (((int)px / size_block) * size_block) + size_block; // looking up
			ry = (px - rx) * Tan + py;
			xo = size_block;
			yo = -xo * Tan;
		}
		if (cos(ra * PI / 180.0) <- 0.001)
		{
			rx = (((int)px / size_block) * size_block) - 0.0001; // looking down
			ry = (px - rx) * Tan + py;
			xo = -size_block;
			xo = -xo * Tan;
		}
		else // looking straight left or right
		{
			printf("ici ?\n");
			rx = px;
			ry = py;
			dof = 8;
		}
		while (dof < 8) // check next horizontal
		{
			printf("la ?\n");
			mx = (int)(rx) / size_block;
			printf("mx = %i\n", mx);
			my = (int)(ry) / size_block;
			printf("my = %i\n", my);
			mp = my * param->map.max_length + mx;
			printf("mp = %i\n", mp);
			if (mp > 0 && mp < param->map.max_length * param->map.nb_lines && param->map.map[mp] == '1')
			{
				distV = distance(px, py, hx, hy, ra);
				dof = 8; // wall hit
			}
			else
			{
				rx = rx + xo;
				ry = ry + yo;
				dof++; // next vertical line
			}
		}
		vx = rx;
		vy = ry;

		//CHECK HORIZONTAL LINES
		dof = 0;
		distH = 1000000;
		Tan = 1.0 / Tan;
		if (sin(ra * PI / 180.0) > 0.001)
		{
			ry = (((int)py / size_block) * size_block) - 0.0001;
			rx = (py - ry) * Tan + px;
			yo = -size_block;
			xo = -yo * Tan;
		}
		if (sin(ra * PI / 180.0) < -0.001)
		{
			ry = (((int)py / size_block) * size_block) + size_block;
			rx = (py - ry) * Tan + px;
			yo = size_block;
			xo = -yo * Tan;
		}
		else // looking straight up or down
		{
			printf("ici2 ?\n");
			rx = px;
			ry = py;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx) / size_block;
			my = (int)(ry) / size_block;
			mp = my * param->map.max_length + mx;
			printf("mp = %i\n", mp);
			if (mp > 0 && mp < param->map.max_length * param->map.nb_lines && param->map.map[mp] == '1')
			{
				printf("map.map[mp] = %c\n", param->map.map[mp]);
				distH = distance(px, py, vx, vy, ra);
				dof = 8; // wall hit
			}
			else
			{
				rx = rx + xo;
				ry = ry + yo;
				dof++; // next horizontal line
			}
		}
		printf("distV = %f distH = %f\n", distV, distH);
		if (distV < distH) // horizontal hit first;
		{
			rx = vx;
			ry = vy;
			distH = distV;
		}
		r++;
		int ca = fixAngle(pa - ra);
		distH = distH * cos(ca * PI / 180.0);
		ra = fixAngle(ra + 30);
	}
}

int		fixAngle(int a)
{
	if (a > 359)
		a = a - 360;
	if (a < 0)
		a = a + 360;
	return (a);
}

void init(t_param *param)
{
	double px;		//player position
	double py;		//player position
	double pdx;		//delta x
	double pdy;		//delta y
	double pa;		//angle of the player

	px = param->perso.position_x;
	py = param->perso.position_y;
	if (param->perso.orientation == 'N')
		pa = 0;
	if (param->perso.orientation == 'S')
		pa = 180;
	if (param->perso.orientation == 'E')
		pa = 90;
	if (param->perso.orientation == 'W')
		pa = 270;
	printf("px = %f\n", px);
	printf("py = %f\n", py);
	printf("pa = %f\n", pa);
	pdx = cos(pa) * 5;
	pdy = sin(pa) * 5;
	printf("pdx = %f\n", pdx);
	printf("pdy = %f\n", pdy);
	drawrays3D(pa, px, py, param);
}
