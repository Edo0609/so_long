#include <so_long.h>

#define WIN_WIDTH 2560
#define WIN_HEIGHT 1440
//max grid 20 x 11 for 128 per grid
//max grid 40 x 22 for 64 per grid
#define GRID 128

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

void fill(t_data *mlx, int onecolor, int secolor)
{
    int x;
    int y;
    int first;
    int second;
    
    y = 0;
    while (y < WIN_HEIGHT)
    {
        if (y %(GRID * 2) < GRID)
        {
            first = onecolor;
            second = secolor;
        }
        else
        {
            first = secolor;
            second = onecolor;
        }
        x = 0;
        while (x < WIN_WIDTH)
        {
            if ((x % (GRID * 2) < GRID))
                put_pixel(mlx, x, y, first);
            else
                put_pixel(mlx, x, y, second);
            x++;
        }
        y++;
    }
}

int main (void)
{
    t_data mlx;

    mlx.mlx = mlx_init();
    mlx.win = mlx_new_window(mlx.mlx, WIN_WIDTH, WIN_HEIGHT, "prueba");
    mlx.img = mlx_new_image(mlx.mlx, WIN_WIDTH, WIN_HEIGHT);
    mlx.address = mlx_get_data_addr(mlx.img, &mlx.bpp, &mlx.line_length, &mlx.endian);
    fill(&mlx, color(0, 255, 255, 255), color(0, 100, 100, 100));
    mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
    mlx_loop(mlx.mlx);
}