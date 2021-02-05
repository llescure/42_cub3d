#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>

int		press_key(int key, void *param)
{
	printf("%d\n", key);
	if (key == 53) // touche esc permet de quitter
		exit (0);
	return (0);
}

int     main(void)
{
    void    *mlx;
    void    *mlx_win;
    void    *img;
    char    *relative_path = "./test.xpm";
    int     img_width;
    int     img_height;

    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, 1920, 1080, "NYAN CAT");
    img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
    mlx_put_image_to_window(mlx, mlx_win, img, 600, 400);
    mlx_key_hook(mlx_win, press_key, (void *) 0);
	mlx_loop(mlx);
}
