#include <so_long.h>

void destroy_textures(t_gdata *game)
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

void end_game(char *str, int status, t_gdata *game)
{
    if (game->win)
        mlx_destroy_window(game->mlx, game->win);
    destroy_textures(game);
    clean_maps(&game->map);
    mlx_loop_end(game->mlx);
    if (game->mlx)
    {
        mlx_destroy_display(game->mlx);
        free(game->mlx);
    }
    if (status == EXIT_FAILURE)
        ft_printf("Error:\n");
    ft_printf("%s\n", str);
    exit(status);
}

void load_texture(void **texture, char *path, t_gdata *game)
{
    int i_w;
    int i_h;

    *texture = mlx_xpm_file_to_image(game->mlx, path, 
    &i_w, &i_h);
    if (i_w != SIZE || i_h != SIZE)
        end_game("one or more textures are not the right size!", EXIT_FAILURE, game);
    if (!*texture)
        end_game("Failed loading texture.", EXIT_FAILURE, game);
}

void init_textures(t_gdata *game)
{
    int i_w;
    int i_h;

    usleep(50000);
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

void check_movement(int new_x, int new_y, t_gdata *game)
{
    if (game->map.map[new_y][new_x] != '1')
    {
		if (game->map.map[new_y][new_x] != 'E' ||
		game->map.map[new_y][new_x] == 'E' && game->c == 0)
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

int keypress(int key, t_gdata *game)
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
    mlx_loop(game->mlx);
}


int main(int ac, char **av)
{
    t_gdata  game;

    init_map(&game.map);
    if (ac != 2)
    {
        map_error("invalid format. Format: ./so_long [MAP]", &game.map);
        return (1);
    }
    ft_printf("for leaks, use the command: valgrind --leak-check=full --show-leak-kinds=all ./so_long %s\n", av[1]);
    readmap(av[1], &game.map);
    check_borders_and_tiles(&game.map);
    print_map(game.map.map);
    valid_check(&game.map);
    init_game(&game);
    return (0);
}