#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>

int		print_image(void *mlx, void *mlx_win, int color)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (x < 2000)
	{
		while (y < 2000)
		{
			mlx_pixel_put(mlx, mlx_win, x, y, color);
			y++;
		}
		x++;
	}
	return (0);
}

int		press_key(int key, void *param, void *mlx, void *mlx_win)
{
	printf("%d\n", key);
	if (key == 53) // touche esc permet de quitter
		exit (0);
	if (key == 0)
		initialisation_window(mlx, mlx_win, 0xFF0000);
	return (0);
}

int		initialisation_image(void *mlx, void *mlx_win, int color)
{
	mlx_clear_window(mlx, mlx_win);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 800, 800, "Hello world!");
	mlx_key_hook(mlx_win, press_key, (void *) 0);
	char *string = "BIENVENUE";
	mlx_string_put(mlx, mlx_win, 400, 0, color, string);
	mlx_loop(mlx);
}

int     main(void)
{
	void *mlx;
	void *mlx_win;
	int color;

	color = 0xFFFFFF;
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 800, 800, "Hello world!");
	mlx_key_hook(mlx_win, press_key, (void *) 0);
	char *string = "BIENVENUE";
	mlx_string_put(mlx, mlx_win, 400, 0, color, string);
	mlx_loop(mlx);
}
