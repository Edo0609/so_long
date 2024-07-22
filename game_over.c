/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_over.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epenaloz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 17:44:25 by epenaloz          #+#    #+#             */
/*   Updated: 2024/07/15 17:44:32 by epenaloz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	clean_maps(t_map *map)
{
	int	i;

	if (map->map)
	{
		i = -1;
		while (map->map[++i])
			free(map->map[i]);
		free(map->map);
	}
	if (map->copy)
	{
		i = -1;
		while (map->copy[++i])
			free(map->copy[i]);
		free(map->copy);
	}
}

void	map_error(const char *str, t_map *map)
{
	ft_printf("Error\n%s\n", str);
	if (map->fd != -1)
		close(map->fd);
	clean_maps(map);
	exit(EXIT_FAILURE);
}

void	destroy_textures(t_gdata *game)
{
	if (game->t_player)
		mlx_destroy_image(game->mlx, game->t_player);
	if (game->t_exit)
		mlx_destroy_image(game->mlx, game->t_exit);
	if (game->t_collect)
		mlx_destroy_image(game->mlx, game->t_collect);
	if (game->t_floor)
		mlx_destroy_image(game->mlx, game->t_floor);
	if (game->t_wall)
		mlx_destroy_image(game->mlx, game->t_wall);
}

void	end_game(char *str, int status, t_gdata *game)
{
	if (game->win)
		mlx_destroy_window(game->mlx, game->win);
	destroy_textures(game);
	clean_maps(&game->map);
	if (game->mlx)
	{
		mlx_destroy_display(game->mlx);
		free(game->mlx);
	}
	if (status == EXIT_FAILURE)
		ft_printf("Error:\n");
	if (status == EXIT_SUCCESS && (game->x_pos == game->exit_x
			&& game->y_pos == game->exit_y))
	{
		ft_printf("\n...and with that, the fate of the penguin species was\n");
		ft_printf("sealed, and humans of today will bear witness to the\n");
		ft_printf("greatness that your kind has brought upon them...\n");
	}
	ft_printf("%s\n", str);
	exit(status);
}
