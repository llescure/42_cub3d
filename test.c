#include <mlx.h>

int     main(void)
{
    void    *mlx;
    void    *mlx_win;

    mlx = mlx_init();
    mlx_win = mlx_new_window(mlx, 500, 500, "Hello world!");
    mlx_loop(mlx);
}
