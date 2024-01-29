/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prueba3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epenaloz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/28 17:45:03 by epenaloz          #+#    #+#             */
/*   Updated: 2024/01/28 17:45:09 by epenaloz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

#define WIN_WIDTH 1280
#define WIN_HEIGTH 720

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

void	put_pixel(t_win *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->address + (y * img->line_length + x * (img->pixel_bits / 8));
	*(unsigned int *)pixel = color;
}

void    fill_screen(t_win *window, int  color)
{
    int x;
    int y;

    y = -1;
    while (++y != WIN_HEIGTH)
    {
        x = -1;
        while(++x != WIN_WIDTH)
        {
            put_pixel(window, x, y, color);
        }
    }
}

int	add_color(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int    next_frame(t_win *window)
{
    static int  loop = 1;

    if (loop == 1)
    {
        fill_screen(window, add_color(0, 255, 0, 0));
        mlx_put_image_to_window(window->mlx, window->win, window->img, 0, 0);
        loop++;
    }
    else if (loop == 2)
    {
        fill_screen(window, add_color(0, 0, 255, 0));
        mlx_put_image_to_window(window->mlx, window->win, window->img, 0, 0);
        loop++;
    }
    else if (loop == 3)
    {
        fill_screen(window, add_color(0, 0, 0, 255));
        mlx_put_image_to_window(window->mlx, window->win, window->img, 0, 0);
        loop = 1;
    }
    usleep(500000);
    return (0);
}

int main(void)
{
    t_win   window;

    window.mlx = mlx_init();
    window.win = mlx_new_window(window.mlx, WIN_WIDTH, WIN_HEIGTH, "prueba animacion");
    window.img = mlx_new_image(window.mlx, WIN_WIDTH, WIN_HEIGTH);
    window.address = mlx_get_data_addr(window.img, &window.pixel_bits, &window.line_length, &window.endian);
    mlx_loop_hook(window.mlx, next_frame, &window);
    mlx_loop(window.mlx);
}