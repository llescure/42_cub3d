#define PI 3.141519
#include "../include/struct_cub3D.h"
#include "../include/cub3D.h"
#include <math.h>

int game_loop(t_param *param, double fPlayerX, double fPlayerY, double fPlayerA)
{
	int x = 0;
	double fFOV = PI / 4.0;
	double fRayAngle;
	int hit = 0;
	double fDepth = 16.0; // taille des blocs
	fRayAngle = (fPlayerA - fFOV / 2.0) + ((double)x / (double)param->map.max_length) * fFOV;
	int fEyeX = sin(fRayAngle);
	int fEyeY = cos(fRayAngle);
	double fDistanceToWall = 0;
	while (x < param->map.max_length)
	{
		while (hit == 0)
		{
			fDistanceToWall += 0.1;
			int nTestX = (int)(fPlayerX + fEyeX * fDistanceToWall);
			int nTestY = (int)(fPlayerY + fEyeY + fDistanceToWall);
			if (nTestX < 0 || nTestX >= param->map.max_length || nTestY < 0 || nTestY >= param->map.nb_lines)
			{
				hit = 1;
				fDistanceToWall = fDepth;
			}
			else
			{
				if (param->map.map[nTestY * param->map.max_length + nTestX] == '1')
				{
					hit = 1;
				}
			}
		}
		int nCeiling = (double)param->map.nb_lines / 2.0) - param->map.max_length / ((double)fDistanceToWall);
		int nFloor = param->map.nb_lines - nCeiling;
		x++;
		printf("distance to wall = %f\n", fDistanceToWall);

		for (y < nCeiling)
		{
			if (y < nCeiling)
			else

		}
	}
	return (0);
}

void init(t_param *param)
{
		double fPlayerX = param->perso.position_x;
		double fPlayerY = param->perso.position_y;
		double fPlayerA;
		if (param->perso.orientation == 'N')
			fPlayerA = 0;
		if (param->perso.orientation == 'S')
			fPlayerA = 180;
		if (param->perso.orientation == 'E')
			fPlayerA = 90;
		if (param->perso.orientation == 'W')
			fPlayerA = 270;
		game_loop(param, fPlayerX, fPlayerY, fPlayerA);
}
