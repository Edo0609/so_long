/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prueba4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epenaloz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 19:59:31 by epenaloz          #+#    #+#             */
/*   Updated: 2024/01/28 19:59:33 by epenaloz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#define WIN_WIDTH 1280
#define WIN_HEIGHT 720
#define SIZE_SQUARE 100

// typedef struct s_win
// {
//     void    *mlx;
//     void    *win;
// }   t_win;

typedef struct s_win{
    void    *mlx;
    void    *win;
    void    *img;
    void    *address;
    int     pixel_bits;
    int     line_length;
    int     endian;
}   t_win;

void    leaks(void)
{
    system("leaks a.out");
}

int	add_color(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

void	put_pixel(t_win *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->address + (y * img->line_length + x * (img->pixel_bits / 8));
	*(unsigned int *)pixel = color;
}

void    clean_screen(t_win *window)
{
    int x;
    int y;

    y = -1;
    while (++y != WIN_HEIGHT)
    {
        x = -1;
        while(++x != WIN_WIDTH)
            put_pixel(window, x, y, add_color(0, 0, 0, 0));
    }
}

void    print_square(t_win *window, int  color, int x, int y)
{
    int horizontal;
    int vertical;
    
    clean_screen(window);
    vertical = -1;
    while (++vertical != SIZE_SQUARE)
    {
        horizontal = -1;
        while (++horizontal != SIZE_SQUARE)
            put_pixel(window, x + horizontal, y + vertical, color);
    }
}

int     move_square(int keycode, t_win *window)
{
    static int  x = (WIN_WIDTH / 2) - (SIZE_SQUARE / 2);
    static int  y = (WIN_HEIGHT / 2) - (SIZE_SQUARE / 2);

    if (keycode == 13)
    {
        y -= SIZE_SQUARE;
        if (y <= 0)
            y = 0;
    }
    else if (keycode == 0)
    {
        x -= SIZE_SQUARE;
        if (x <= 0)
            x = 0;
    }
    else if (keycode == 2)
    {
        x += SIZE_SQUARE;
        if (x + SIZE_SQUARE >= WIN_WIDTH)
        x = WIN_WIDTH - SIZE_SQUARE;
    }
    else if (keycode == 1)
    {
        y += SIZE_SQUARE;
        if (y + SIZE_SQUARE >= WIN_HEIGHT)
        y = WIN_HEIGHT - SIZE_SQUARE;
    }
    print_square(window, add_color(0, 255, 0, 0), x, y);
    mlx_put_image_to_window(window->mlx, window->win, window->img, 0, 0);
    return (0);
}

// int    next_frame(t_win *window)
// {
//     return (0);
// }

int main(void)
{
    t_win   window;

    atexit(leaks);
    window.mlx = mlx_init();
    window.win = mlx_new_window(window.mlx, WIN_WIDTH, WIN_HEIGHT, "movimiento cuadrado");
    window.img = mlx_new_image(window.mlx, WIN_WIDTH, WIN_HEIGHT);
    window.address = mlx_get_data_addr(window.img, &window.pixel_bits, &window.line_length, &window.endian);
    print_square(&window, add_color(0, 255, 0, 0), (WIN_WIDTH / 2) - (SIZE_SQUARE / 2), (WIN_HEIGHT / 2) - (SIZE_SQUARE / 2));
    mlx_put_image_to_window(window.mlx, window.win, window.img, 0, 0);
    mlx_hook(window.win, 2, 0L, move_square, &window);
    //mlx_loop_hook(window.mlx, next_frame, &window);
    mlx_loop(window.mlx);
}