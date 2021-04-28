#include "../include/struct_cub3d.h"
#include "../include/cub3d.h"

double	shadow_texture(double distance, char addr)
{
	double shadow;

	shadow = distance / 6;
	if (shadow < 1)
		shadow = 1;
	return ((addr & 0xff) / shadow);
}
