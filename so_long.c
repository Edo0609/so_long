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

void init_map(t_map *map)
{
    map->height = 0;
    map->width = 0;
    map->map = NULL;
	map->copy = NULL;
	map->collectable = 0;
	map->exit = 0;
	map->player = 0;
}

void init_game(t_gdata *game)
{
    int width;
    int height;

    width = game->map.width * SIZE;
    height = game->map.height * SIZE;
    game->mlx = mlx_init();
    game->win = mlx_new_window(game->mlx, width, height, "so_long");
    game->c = game->map.collectable;
	game->moves = 0;
    init_textures(game);
    load_map(game);
    mlx_hook(game->win, 02, 1L<<0, keypress, game);
    mlx_hook(game->win, 17, 1L<<17, close_win, game);
    mlx_loop(game->mlx);
}

int main(int ac, char **av)
{
    t_gdata  game;

    if (ac != 2)
    {
        ft_printf("Error:\ninvalid format. Format: ./so_long [MAP]");
        return (1);
    }
    init_map(&game.map);
    readmap(av[1], &game.map);
    check_borders_and_tiles(&game.map);
    print_map(game.map.map);
    valid_check(&game.map);
    init_game(&game);
    return (0);
}