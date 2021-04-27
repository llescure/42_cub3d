#include "../include/struct_cub3d.h"
#include "../include/cub3d.h"

double	shadow_texture(double distance)
{
	double shadow;

	shadow = distance / 3;
	if (shadow < 1)
		shadow = 1;
	return (shadow);
}
