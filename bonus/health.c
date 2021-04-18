#include "../include/struct_cub3d.h"
#include "../include/cub3d.h"

int	health_management(t_data *data)
{
	if (data->bonus.life == 5)
	else if (data->bonus.health == 4)
	else if (data->bonus.health == 3)
	else if (data->bonus.health == 2)
	else if (data->bonus.health == 1)
	else if (data->bonus.health == 0)
	{
		print_error(&data->param, "Game over");
		return (-1);
	}
}
