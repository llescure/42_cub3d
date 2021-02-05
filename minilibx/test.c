#include <mlx.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct  s_all {
    void        *mlx;
    void        *win;
}               t_all;

typedef struct  s_image {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_image;

int		press_key(int key, void *param, void *mlx)
{
    t_all   all;

	printf("%d\n", key);
	if (key == 53) // touche esc permet de quitter
		exit (0);
    if (key == 0)
    {
        mlx_clear_window(all.mlx, all.win);
    }
	return (0);
}

void    my_mlx_pixel_put(t_image *data, int x, int y, int color) //mettre un pixel de couleur sur l'image
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}

int     main(void)
{
    t_all   all;
	t_image img;

	all.mlx = mlx_init();
	all.win = mlx_new_window(all.mlx, 1920, 1080, "HELLO");
	img.img = mlx_new_image(all.mlx, 100, 100);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								 &img.endian);
	my_mlx_pixel_put(&img, 50, 50, 0x00FF0000);
    mlx_key_hook(all.win, press_key, &all);
 	mlx_put_image_to_window(all.mlx, all.win, img.img, 500, 500);
	mlx_loop(all.mlx);
}
