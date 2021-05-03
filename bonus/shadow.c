/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 20:25:38 by llescure          #+#    #+#             */
/*   Updated: 2021/05/03 20:25:40 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
