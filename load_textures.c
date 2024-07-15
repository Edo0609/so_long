/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epenaloz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:12:33 by epenaloz          #+#    #+#             */
/*   Updated: 2024/07/15 18:12:37 by epenaloz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void load_texture(void **texture, char *path, t_gdata *game)
{
    int i_w;
    int i_h;

    *texture = mlx_xpm_file_to_image(game->mlx, path, 
    &i_w, &i_h);
    if (i_w != SIZE || i_h != SIZE)
        end_game("invalid size for one or more textures!", EXIT_FAILURE, game);
    if (!*texture)
        end_game("Failed loading texture.", EXIT_FAILURE, game);
}

void init_textures(t_gdata *game)
{

    load_texture(&game->t_player, "textures/player.xpm", game);
    load_texture(&game->t_collect, "textures/collectable.xpm", game);
    load_texture(&game->t_exit, "textures/exit_c.xpm", game);
    load_texture(&game->t_floor, "textures/floor.xpm", game);
    load_texture(&game->t_wall, "textures/wall.xpm", game);
}

void put_image(int x, int y, char texture, t_gdata *game)
{
    if (texture == 'P')
    {
        mlx_put_image_to_window(game->mlx, game->win, game->t_player, x, y);
        game->x_pos = x / SIZE;
        game->y_pos = y / SIZE;
    }
    else if (texture == 'E')
    {
        mlx_put_image_to_window(game->mlx, game->win, game->t_exit, x, y);
        game->exit_x = x / SIZE;
        game->exit_y = y / SIZE;
    }
    else if (texture == '1')
        mlx_put_image_to_window(game->mlx, game->win, game->t_wall, x, y);
    else if (texture == '0')
        mlx_put_image_to_window(game->mlx, game->win, game->t_floor, x, y);
    else if (texture == 'C')
        mlx_put_image_to_window(game->mlx, game->win, game->t_collect, x, y);
}

void load_map(t_gdata *game)
{
    int i;
    int j;

    j = -1;
    while (game->map.map[++j])
    {
        i = -1;
        while (game->map.map[j][++i])
            put_image(i * SIZE, j * SIZE, game->map.map[j][i], game);
    }
}
