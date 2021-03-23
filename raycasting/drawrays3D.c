#include "../include/struct_cub3D.h"
#include "../include/cub3D.h"
#include <math.h>
#define PI 3.1415926535
#define P2 PI/2
#define P3 3 * PI/2
#define D 0.0174533 // 1 degree in radians

// C'EST QUOI PA PUTAIN

void buttons(unsigned char key, int x, int y)
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

double		distance(double ax, double ay, double bx, double by, double ang)
{
	return (sqrt((bx - ax ) * (bx - ax) + (by - ay) * (by - ay)));
}

void drawrays3D()
{
	int r;
	int mx;
	int my;
	int mp;
	int dof;
	double rx;
	double ry;
	double ra;
	double xo;
	double xy;
	double aTan = -1/tan(ra);
	double nTan = -tan(ra);
	double distH = 1000000;
	double hx = px;
	double hy = py;
	double distV = 1000000;
	double vx = px;
	double vy = py;
	ra = pa - D;
	if (ra < 0)
		ra += 2 * PI;
	if (ra > 2 * PI)
		ra = -= 2 * PI;
	r = 0; // number of rays
	ra = pa;
	while (r < 1) // nombre de rayons qu'il y aura, si >1 liberer le morceau de code
	{
		//CHECK HORIZONTAL LINES
		dof = 0;
		if (ra > PI)
		{
			ry = (((int)py / 64) * 64) * 0.0001; // looking up
			rx = (py - ry) * aTan + px;
			yo = -64;
			xo = -yo * aTan;
		}
		if (ra < PI)
		{
			ry = (((int)py / 64) * 64) + 64; // looking down
			rx = (py - ry) * aTan + px;
			yo = 64;
			xo = -yo * aTan;
		}
		if (ra == 0 || ra == PI) // looking straight left or right
		{
			rx = px;
			ry = py;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx) / 64;
			my = (int)(ry) / 64;
			mp = my * param->map.max_length + mx;
			if (mp > 0 && mp < param->map.max_length * param->map.nb_lines && param->map.map[mp] == 1)
			{
				hx = rx;
				hy = ry;
				distH = distance(px, py, hx, hy, ra);
				dof = 8; // wall hit
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1; // next horizontal line
			}
		}
		//CHECK VERTICAL LINES
		dof = 0;
		if (ra > P2 && ra < P3)
		{
			rx = (((int)px / 64) * 64) * 0.0001; // looking left
			ry = (px - rx) * nTan + py;
			xo = -64;
			yo = -xo * nTan;
		}
		if (ra < P2 || ra > P3)
		{
			rx = (((int)px / 64) * 64) + 64; // looking right
			ry = (px - rx) * nTan + py;
			xo = 64;
			yo = -xo * nTan;
		}
		if (ra == 0 || ra == PI) // looking straight up or down
		{
			rx = px;
			ry = py;
			dof = 8;
		}
		while (dof < 8)
		{
			mx = (int)(rx) / 64;
			my = (int)(ry) / 64;
			mp = my * param->map.max_length + mx;
			if (mp > 0 && mp < param->map.max_length * param->map.nb_lines && param->map.map[mp] == 1)
			{
				vx = rx;
				vy = ry;
				distV = distance(px, py, vx, vy, ra);
				dof = 8; // wall hit
			}
			else
			{
				rx += xo;
				ry += yo;
				dof += 1; // next horizontal line
			}
		}
		if (distV < distH)
		{
			rx = vx;
			ry = vy;
		}
		if (distH < distV)
		{
			rx = hx;
			ry = hy;
		}
		r++;
/*		ra += DR;
		if (ra < 0)
			ra += 2 * PI;
		if (ra > 2 * PI)
			ra = -= 2 * PI;
*/	}
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
	printf("px = %f\n", px);
	printf("py = %f\n", py);
//	pdx =cos(pa) * 5;
//	pdy = sin(pa) * 5;

}
