/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_and_movement.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epenaloz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:01:53 by epenaloz          #+#    #+#             */
/*   Updated: 2024/07/15 18:01:55 by epenaloz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	check_movement(int new_x, int new_y, t_gdata *game)
{
	if (game->map.map[new_y][new_x] != '1')
	{
		if (game->map.map[new_y][new_x] != 'E' ||
		(game->map.map[new_y][new_x] == 'E' && game->c == 0))
		{
			ft_printf("Move Counter: %d\n", ++game->moves);
			if (game->map.map[new_y][new_x] == 'E' && game->c == 0)
				end_game("You Win! Congratulations!", EXIT_SUCCESS, game);
			if (game->map.map[new_y][new_x] == 'C')
				game->c--;
			game->map.map[game->y_pos][game->x_pos] = '0';
			game->y_pos = new_y;
			game->x_pos = new_x;
			game->map.map[game->y_pos][game->x_pos] = 'P';
		}
	}
	if (game-> c == 0)
	{
		mlx_destroy_image(game->mlx, game->t_exit);
		load_texture(&game->t_exit, "textures/exit_o.xpm", game);
	}
	load_map(game);
}

int	keypress(int key, t_gdata *game)
{
	if (key == ESC)
		end_game("Game closed with ESC key", EXIT_SUCCESS, game);
	if (key == W_KEY || key == UP)
		check_movement(game->x_pos, game->y_pos - 1, game);
	else if (key == A_KEY || key == LEFT)
		check_movement(game->x_pos - 1, game->y_pos, game);
	else if (key == S_KEY || key == DOWN)
		check_movement(game->x_pos, game->y_pos + 1, game);
	else if (key == D_KEY || key == RIGHT)
		check_movement(game->x_pos + 1, game->y_pos, game);
	return (0);
}

int	close_win(t_gdata *game)
{
	end_game("Window Closed with x button.", EXIT_SUCCESS, game);
	return (0);
}
