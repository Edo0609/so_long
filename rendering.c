#include <so_long.h>

void game_error(char *str, t_gdata *game)
{
    map_error(str, &game->map);
}

void init_textures(t_gdata *game)
{
    int i_w;
    int i_h;

    game->t_exit = mlx_xpm_file_to_image(game->mlx, "maps/exit.xpm", 
    &i_w, &i_h);
    if (i_w != SIZE || i_h != SIZE)
        game_error("textures are not the right size!", game);
    game->t_player = mlx_xpm_file_to_image(game->mlx, "maps/player.xpm", 
    &i_w, &i_h);
    if (i_w != SIZE || i_h != SIZE)
        game_error("textures are not the right size!", game);
    game->t_wall = mlx_xpm_file_to_image(game->mlx, "maps/wall.xpm", 
    &i_w, &i_h);
    if (i_w != SIZE || i_h != SIZE)
        game_error("textures are not the right size!", game);
    game->t_wall = mlx_xpm_file_to_image(game->mlx, "maps/wall.xpm", 
    &i_w, &i_h);
    if (i_w != SIZE || i_h != SIZE)
        game_error("textures are not the right size!", game);
    game->t_collect = mlx_xpm_file_to_image(game->mlx, "maps/collectable.xpm", 
    &i_w, &i_h);
    if (i_w != SIZE || i_h != SIZE)
        game_error("textures are not the right size!", game);
}

void init_game(t_gdata *game)
{
    int width;
    int height;

    width = game->map.width * SIZE;
    height = game->map.height * SIZE;
    game->mlx = mlx_init();
    game->win = mlx_new_window(game->mlx, width, height, "so_long");
    game->img = mlx_new_image(game->mlx, width, height);
    game->addr = mlx_get_data_addr(game->img, &game->bpp, 
    &game->ll, &game->endian);
    //init_textures();
}


int main(int ac, char **av)
{
    t_gdata  game;

    if (ac != 2)
    {
        map_error("invalid format. Format: ./so_long [MAP]", &game.map);
        return (1);
    }
    init_map(&game.map);
    ft_printf("for leaks, use the command: valgrind --leak-check=full --show-leak-kinds=all ./so_long %s\n", av[1]);
    readmap(av[1], &game.map);
    check_borders_and_tiles(&game.map);
    print_map(game.map.map);
    valid_check(&game.map);
    init_game(&game);
    clean_maps(&game.map);
    return (0);
}