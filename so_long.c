/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epenaloz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:09:39 by epenaloz          #+#    #+#             */
/*   Updated: 2024/07/15 18:09:43 by epenaloz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	init_map(t_map *map)
{
	map->height = 0;
	map->width = 0;
	map->map = NULL;
	map->copy = NULL;
	map->collectable = 0;
	map->exit = 0;
	map->player = 0;
	map->start = 0;
}

void	init_game_to_null(t_gdata *game)
{
	game->mlx = NULL;
	game->win = NULL;
	game->t_player = NULL;
	game->t_floor = NULL;
	game->t_wall = NULL;
	game->t_exit = NULL;
	game->t_collect = NULL;
	game->x_pos = 0;
	game->y_pos = 0;
	game->c = game->map.collectable;
	game->moves = 0;
	game->exit_x = 0;
	game->exit_y = 0;
}

void	init_game(t_gdata *game)
{
	int	width;
	int	height;
	int	screen_x;
	int	screen_y;

	width = game->map.width * SIZE;
	height = game->map.height * SIZE;
	init_game_to_null(game);
	game->mlx = mlx_init();
	if (!game->mlx)
		end_game("Failed loading mlx interface.", EXIT_FAILURE, game);
	mlx_get_screen_size(game->mlx, &screen_x, &screen_y);
	if (screen_x < width || screen_y < height)
		end_game("map is too big!", EXIT_FAILURE, game);
	init_textures(game);
	game->win = mlx_new_window(game->mlx, width, height, "so_long");
	if (!game->win || width <= 0 || height <= 0)
		end_game("Failed creating window.", EXIT_FAILURE, game);
	load_map(game);
	mlx_hook(game->win, 02, 1L << 0, keypress, game);
	mlx_hook(game->win, 17, 1L << 17, close_win, game);
	mlx_loop(game->mlx);
}

int	main(int ac, char **av)
{
	t_gdata	game;

	if (ac != 2)
	{
		ft_printf("Error:\ninvalid format. Format: ./so_long [MAP]");
		return (1);
	}
	init_map(&game.map);
	readmap(av[1], &game.map);
	check_borders_and_tiles(&game.map);
	ft_printf("Map visualization:\n");
	print_map(game.map.map);
	valid_check(&game.map);
	init_game(&game);
	return (0);
}
