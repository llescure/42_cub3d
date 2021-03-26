#include "../include/struct_cub3D.h"
#include "../include/cub3D.h"
#include <math.h>

void test_ligne_direct(double px, double py, double pa, t_param *param)
{
//	double	mx; // coordonnees du mur
//	double my;
	int rx;
	int ry; // coordonnees du rayon
//	int fov = 60;
	double distance;
	double hp;
	double h_min;
	double h_max;
	int r; // rayon

	rx = px;
	ry = py;
	r = 0;

	// HORIZONTAL
	if (pa == 90)
	{
		while (rx >= 0 && rx < param->map.max_length)
		{
			if (param->map.tab_map[ry][rx] == '1')
			{
				distance = (px - rx) * (px - rx) + (py - ry) * (py - ry);
				printf("distance = %f\n", distance);
				hp = (3 / distance) * 0.2; // 3 = high of the wall, 0.2 = distance from the screen
			}
			rx++;
		}
	}
	if (pa == 270)
	{
		while (rx >= 0 && rx < param->map.max_length)
		{
			if (param->map.tab_map[ry][rx] == '1')
			{
				distance = (px - rx) * (px - rx) + (py - ry) * (py - ry);
				printf("distance = %f\n", distance);
				hp = (3 / distance) * 0.2; // 3 = high of the wall, 0.2 = distance from the screen
			}
			rx--;
		}
	}
	// VERTICAL
	if (pa == 180)
	{
		while (ry >= 0 && ry < param->map.nb_lines)
		{
			if (param->map.tab_map[ry][rx] == '1')
			{
				distance = (px - rx) * (px - rx) + (py - ry) * (py - ry);
				printf("distance = %f\n", distance);
				hp = (3 / distance) * 0.2; // 3 = high of the wall, 0.2 = distance from the screen
			}
			ry++;
		}
	}
	if (pa == 0)
	{
		while (ry >= 0 && ry < param->map.nb_lines)
		{
			if (param->map.tab_map[ry][rx] == '1')
			{
				distance = (px - rx) * (px - rx) + (py - ry) * (py - ry);
				printf("distance = %f\n", distance);
				hp = (3 / distance) * 0.2; // 3 = high of the wall, 0.2 = distance from the screen
			}
			ry--;
		}
	}
	h_min = 1.8 - hp / 2; // 1.8 = height of the player
	h_max =  1.8 + hp / 2;
	printf("h_min = %f h_max = %f\n", h_min, h_max);
}


void init(t_param *param)
{
	int px;		//player position
	int py;		//player position
	int pdx;		//delta x
	int pdy;		//delta y
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
	printf("px = %i\n", px);
	printf("py = %i\n", py);
	printf("pa = %f\n", pa);
	pdx = cos(pa) * 5;
	pdy = sin(pa) * 5;
	printf("pdx = %i\n", pdx);
	printf("pdy = %i\n", pdy);
//	drawrays3D(pa, px, py, param);
	test_ligne_direct(px, py, pa, param);
}
