#include <so_long.h>

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720

typedef struct s_data 
{
    void    *mlx;
    void    *win;
    void    *img;
    char    *address;
    int     bpp;
    int     line_length;
    int     endian;
}   t_data;

int color(int t, int r, int g, int b)
{
    return (t << 24 | r << 16 | g << 8 | b);
}

void put_pixel(t_data *mlx, int x, int y, int color)
{
    char *pos;

    pos = mlx->address + ((y * mlx->line_length) + (x * mlx->bpp / 8));
    *(unsigned int *)pos = color;
}

void fill_color(t_data *mlx, int color)
{
    int x;
    int y;

    y = 0;
    while (y < WIN_HEIGHT)
    {
        x = 0;
        while (x < WIN_WIDTH)
        {
            put_pixel(mlx, x, y, color);
            x++;
        }
        y++;
    }
}

int splash(t_data *mlx)
{
    static int rgb = 1;

    if (rgb % 3 == 1)
    {
        fill_color(mlx, color(0, 255, 0, 0));
    }
    else if (rgb % 3 == 2)
    {
        fill_color(mlx, color(0, 0, 255, 0));
    }
    else
    {
        fill_color(mlx, color(0, 0, 0, 255));
    }
    rgb++;
    mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
    usleep(500000);
    return (0);

}

int main (void)
{
    t_data mlx;

    mlx.mlx = mlx_init();
    mlx.win = mlx_new_window(mlx.mlx, WIN_WIDTH, WIN_HEIGHT, "prueba");
    mlx.img = mlx_new_image(mlx.mlx, WIN_WIDTH, WIN_HEIGHT);
    mlx.address = mlx_get_data_addr(mlx.img, &mlx.bpp, &mlx.line_length, &mlx.endian);
    mlx_loop_hook(mlx.mlx, splash, &mlx);
    mlx_loop(mlx.mlx);
}