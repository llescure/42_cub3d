/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement_keys.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 20:22:21 by llescure          #+#    #+#             */
/*   Updated: 2021/05/03 20:22:24 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/struct_cub3d.h"
#include "../include/cub3d.h"

void	rotate_camera_left(t_data *data)
{
	double old_dirx;
	double old_planx;
	double cosi;
	double sinus;

	old_planx = data->ray.plan_x;
	old_dirx = data->ray.dir_x;
	cosi = cos(2.5 * M_PI / 180);
	sinus = sin(2.5 * M_PI / 180);
	data->ray.dir_x = data->ray.dir_x * cosi - data->ray.dir_y * sinus;
	data->ray.dir_y = old_dirx * sinus + data->ray.dir_y * cosi;
	data->ray.plan_x = data->ray.plan_x * cosi - data->ray.plan_y * sinus;
	data->ray.plan_y = old_planx * sinus + data->ray.plan_y * cosi;
	data->param.perso.angle += 2.5;
	if (data->param.perso.angle > 360)
		data->param.perso.angle -= 360;
}

void	rotate_camera_right(t_data *data)
{
	double old_dirx;
	double old_planx;
	double cosi;
	double sinus;

	old_planx = data->ray.plan_x;
	old_dirx = data->ray.dir_x;
	cosi = cos(-2.5 * M_PI / 180);
	sinus = sin(-2.5 * M_PI / 180);
	data->ray.dir_x = data->ray.dir_x * cosi - data->ray.dir_y * sinus;
	data->ray.dir_y = old_dirx * sinus + data->ray.dir_y * cosi;
	data->ray.plan_x = data->ray.plan_x * cosi - data->ray.plan_y * sinus;
	data->ray.plan_y = old_planx * sinus + data->ray.plan_y * cosi;
	data->param.perso.angle -= 2.5;
	if (data->param.perso.angle <= 0)
		data->param.perso.angle += 360;
}

void	left_right_movement(int nega, t_perso *perso)
{
	if ((perso->angle >= 30 && perso->angle < 60) ||
			(perso->angle >= 210 && perso->angle <= 240))
	{
		perso->dirx = nega * -sin(perso->angle * M_PI / 180 + 90);
		perso->diry = nega * -cos(perso->angle * M_PI / 180 + 90);
	}
	else if ((perso->angle >= 120 && perso->angle < 178) ||
			(perso->angle >= 300 && perso->angle <= 330))
	{
		perso->dirx = nega * -sin(perso->angle * M_PI / 180 - 90);
		perso->diry = nega * -cos(perso->angle * M_PI / 180 - 90);
	}
	else if ((perso->angle >= 0 && perso->angle < 30) ||
			(perso->angle > 330 && perso->angle <= 360))
	{
		perso->dirx = nega * sin(perso->angle * M_PI / 180);
		perso->diry = nega * cos(perso->angle * M_PI / 180);
	}
	else if ((perso->angle >= 180 && perso->angle < 210))
	{
		perso->dirx = -1 * nega * -sin(perso->angle * M_PI / 180);
		perso->diry = -1 * nega * -cos(perso->angle * M_PI / 180);
	}
	else
		general_case(nega, perso);
}

void	general_case(int nega, t_perso *perso)
{
	perso->dirx = -1 * nega * sin(perso->angle * M_PI / 180);
	perso->diry = -1 * nega * cos(perso->angle * M_PI / 180);
}

void	forward_backward_movement(int nega, t_perso *perso)
{
	if ((perso->angle >= 0 && perso->angle < 60) || (perso->angle >= 165 &&
				perso->angle < 240)
			|| (perso->angle >= 330 && perso->angle < 360))
	{
		perso->dirx = nega * cos(perso->angle * M_PI / 180);
		perso->diry = nega * sin(perso->angle * M_PI / 180);
	}
	else
	{
		perso->dirx = nega * cos(perso->angle * M_PI / 180);
		perso->diry = nega * sin(perso->angle * M_PI / 180);
	}
}
