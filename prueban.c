#include <so_long.h>

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720
#define SQR_SIDE 200
#define W_KEY 119
#define A_KEY 97
#define S_KEY 115
#define D_KEY 100
#define UP 65362
#define LEFT 65361
#define DOWN 65364
#define RIGHT 65363

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

void refresh(t_data *mlx)
{
    int x;
    int y;

    y = 0;
    while (y < WIN_HEIGHT)
    {
        x = 0;
        while (x < WIN_WIDTH)
        {
            put_pixel(mlx, x, y, color(0, 0, 0, 0));
            x++;
        }
        y++;
    }
}

void make_square(t_data *mlx, int x, int y, int side, int color)
{
    int i;
    int j;

    refresh(mlx);
    j = 0;
    while (j < side)
    {
        i = 0;
        while (i < side)
        {
            put_pixel(mlx, x + i, y + j, color);
            i++;
        }
        j++;
    }
}

int button_opt(int keycode, t_data *mlx)
{
    static int x = WIN_WIDTH / 2 - SQR_SIDE / 2;
    static int y = WIN_HEIGHT / 2 - SQR_SIDE / 2;

    ft_printf("button: %d\n", keycode);
    if (keycode == 65307)
    {
        mlx_destroy_window(mlx->mlx, mlx->win);
        exit(EXIT_SUCCESS);
    }
    else if (keycode == UP || keycode == W_KEY)
    {
        y -= SQR_SIDE;
        if (y < 0)
            y = 0;
    }
    else if (keycode == LEFT || keycode == A_KEY)
    {
        x -= SQR_SIDE;
        if (x < 0)
            x = 0;
    }
    else if (keycode == DOWN || keycode == S_KEY)
    {
        y += SQR_SIDE;
        if (y + SQR_SIDE >= WIN_HEIGHT)
            y = WIN_HEIGHT - SQR_SIDE;
    }
    else if (keycode == RIGHT || keycode == D_KEY)
    {
        x += SQR_SIDE;
        if (x + SQR_SIDE >= WIN_WIDTH)
            x = WIN_WIDTH - SQR_SIDE;
    }
    make_square(mlx, x, y, SQR_SIDE, color(0, 13, 234, 223));
    mlx_put_image_to_window(mlx->mlx, mlx->win, mlx->img, 0, 0);
    return (0);
}

int click(int mbutton, int x, int y, t_data *mlx)
{
    ft_printf("click with button %d! at x=%d and y=%d\n", mbutton, x, y);
    return (0);
}

int close_win(t_data *mlx)
{
    mlx_destroy_window(mlx->mlx, mlx->win);
    ft_printf("DESTROYED!\n");
    exit(EXIT_SUCCESS);
}

int main (void)
{
    t_data mlx;

    mlx.mlx = mlx_init();
    mlx.win = mlx_new_window(mlx.mlx, WIN_WIDTH, WIN_HEIGHT, "prueba");
    mlx.img = mlx_new_image(mlx.mlx, WIN_WIDTH, WIN_HEIGHT);
    mlx.address = mlx_get_data_addr(mlx.img, &mlx.bpp, &mlx.line_length, &mlx.endian);
    usleep(50000);
    make_square(&mlx, (WIN_WIDTH / 2 - SQR_SIDE / 2), (WIN_HEIGHT / 2 - SQR_SIDE / 2), SQR_SIDE, color(0, 14, 234, 223));
    mlx_put_image_to_window(mlx.mlx, mlx.win, mlx.img, 0, 0);
    mlx_hook(mlx.win, 2, 1L<<0, button_opt, &mlx);
    mlx_hook(mlx.win, 4, 1L<<2, click, &mlx);
    mlx_hook(mlx.win, 17, 0L, close_win, &mlx);
    mlx_loop(mlx.mlx);
}