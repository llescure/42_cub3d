/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sound.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llescure <llescure@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/03 20:25:30 by llescure          #+#    #+#             */
/*   Updated: 2021/05/03 22:35:48 by llescure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/struct_cub3d.h"
#include "../include/cub3d.h"

int		init_music(t_data *data)
{
	int return_value;

	if (!(data->img.sound = malloc(sizeof(t_sound))))
		print_error(&data->param, "No music");
	ft_bzero(data->img.sound, sizeof(t_sound));
	data->img.sound->last_start_song = clock();
	return_value =
	system("aplay -q bonus/sound/white_walkers.wav &>/dev/null &");
	return (return_value);
}

int		play_music(t_data *data)
{
	long	clk_tck;
	clock_t	actual_time;
	int		return_value;

	return_value = 0;
	actual_time = clock();
	clk_tck = CLOCKS_PER_SEC;
	if ((double)(actual_time - data->img.sound->last_start_song)
		/ (double)clk_tck >= 129.5)
	{
		return_value = system("killall -9 aplay");
		return_value =
		system("aplay -q bonus/sound/white_walkers.wav &>/dev/null &");
		data->img.sound->last_start_song = actual_time;
	}
	return (return_value);
}
