#include "../include/struct_cub3D.h"
#include "../include/cub3D.h"
#include <math.h>

void test_ligne_direct(double px, double py, double pa, t_param *param)
{
//	double	mx; // coordonnees du mur
//	double my;
	int rx;
	int ry; // coordonnees du rayon
	double distance;
	double hauteur;

	rx = px;
	ry = py;

	// HORIZONTAL
	if (pa == 90)
	{
		while (rx >= 0 && rx < param->map.max_length)
		{
			if (param->map.tab_map[ry][rx] == '1')
			{
				distance = (px - py) * (px - py) + (rx - ry) * (rx - ry);
				printf("distance = %f\n", distance);
				hauteur = tan(1.5 / distance) * distance;
				printf("hauteur = %f\n", hauteur);
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
				distance = (px - py) * (px - py) + (rx - ry) * (rx - ry);
				printf("distance = %f\n", distance);
				hauteur = tan(1.5 / distance) * distance;
				printf("hauteur = %f\n", hauteur);
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
				distance = (px - py) * (px - py) + (rx - ry) * (rx - ry);
				printf("distance = %f\n", distance);
				hauteur = tan(1.5 / distance) * distance;
				printf("hauteur = %f\n", hauteur);
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
				distance = (px - py) * (px - py) + (rx - ry) * (rx - ry);
				printf("distance = %f\n", distance);
				hauteur = tan(1.5 / distance) * distance;
				printf("hauteur = %f\n", hauteur);
			}
			ry--;
		}
	}
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
