#include "../include/struct_cub3d.h"
#include "../include/cub3d.h"

void 	init_music(t_data *data)
{
	if (!(data->img.sound = malloc(sizeof(t_sound))))
		print_error(&data->param, "No music");
	ft_bzero(data->img.sound, sizeof(t_sound));
	data->img.sound->last_start_song = clock();
	system("afplay bonus/sound/maintheme.mp3 &>/dev/null &");
}

void	play_music(t_data *data)
{
	long	clk_tck;
	clock_t	actual_time;

	actual_time = clock();
	clk_tck = CLOCKS_PER_SEC;
	if ((double)(actual_time - data->img.sound->last_start_song)
		/ (double)clk_tck >= 129.5)
	{
		system("killall afplay");
		system("afplay bonus/sound/maintheme.mp3 &>/dev/null &");
		data->img.sound->last_start_song = actual_time;
	}
}
