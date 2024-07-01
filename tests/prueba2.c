/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prueba2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epenaloz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 17:30:22 by epenaloz          #+#    #+#             */
/*   Updated: 2024/01/28 17:36:41 by epenaloz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

void	leaks(void)
{
	system("leaks a.out");
}

typedef struct s_win
{
    void    *mlx;
    void    *win;
}   t_win;

int esc_win(int keycode, t_win *window)
{
    if (keycode == 53)
	{
        mlx_destroy_window(window->mlx, window->win);
		exit(EXIT_SUCCESS);
	}
    return (0);
}

int	x_win(t_win *window)
{
	mlx_destroy_window(window->mlx, window->win);
	ft_printf("Window closed using red cross\n");
	exit(EXIT_SUCCESS);
	return (0);
}

int	mouse_pos(int button, int x, int y)
{
	if (button == 1)
		ft_printf("click! x = %d, y = %d\n", x, y);
	return (0);
}

int	mouse_move(int x, int y)
{
	static int prev_x = -1;
	static int prev_y = -1;
	if (x >= 0 && y >= 0 && prev_x != x && prev_y != y)
		ft_printf("position: %d, %d\n", x, y);
	prev_x = x;
	prev_y = y;
	return (0);
}

int main(void)
{
    t_win   window;
	
	atexit(leaks);
    window.mlx = mlx_init();
    window.win = mlx_new_window(window.mlx, 1280, 720, "eventos prueba");
    mlx_hook(window.win, 2, 1L<<0, esc_win, &window);
	mlx_hook(window.win, 17, 0L, x_win, &window);
	mlx_hook(window.win, 4, 0L, mouse_pos, &window);
	//mlx_hook(window.win, 6, 0L, mouse_move, &window);
    mlx_loop(window.mlx);
}
