#include <so_long.h>

// void load_map(t_gdata *game)
// {
//     int i;
//     int j;

//     j = -1;
//     while (game->map.map[++j])
//     {
//         i = -1;
//         while (game->map.map[j][++i])
//         {
//             if (game->map.map[j][i] = 'P')
//                 mlx_put_image_to_window(game->mlx, game->win, game->t_player, 
//                 i * SIZE, j * SIZE);
//             else if (game->map.map[j][i] = 'E')
//                 mlx_put_image_to_window(game->mlx, game->win, game->t_exit, 
//                 i * SIZE, j * SIZE);
//             else if (game->map.map[j][i] = 'C')
//                 mlx_put_image_to_window(game->mlx, game->win, game->t_collect, 
//                 i * SIZE, j * SIZE);
//             else if (game->map.map[j][i] = '1')
//                 mlx_put_image_to_window(game->mlx, game->win, game->t_wall, 
//                 i * SIZE, j * SIZE);
//             else
//                 mlx_put_image_to_window(game->mlx, game->win, game->t_floor, 
//                 i * SIZE, j * SIZE);
//         }
//     }
// }

void init_textures(t_gdata *game)
{
    int i_w;
    int i_h;

    game->t_exit = mlx_xpm_file_to_image(game->mlx, "textures/exit_c.xpm", 
    &i_w, &i_h);
    ft_printf("width = %d, height = %d", i_w, i_h);
    if (i_w != SIZE || i_h != SIZE || !game->t_exit)
        ft_printf("fuck");
    game->t_player = mlx_xpm_file_to_image(game->mlx, "textures/player.xpm", 
    &i_w, &i_h);
    if (i_w != SIZE || i_h != SIZE || !game->t_player)
        ft_printf("fuck");
    game->t_floor = mlx_xpm_file_to_image(game->mlx, "textures/floor.xpm", 
    &i_w, &i_h);
    if (i_w != SIZE || i_h != SIZE || !game->t_floor)
        ft_printf("fuck");
    game->t_wall = mlx_xpm_file_to_image(game->mlx, "textures/wall.xpm", 
    &i_w, &i_h);
    if (i_w != SIZE || i_h != SIZE || !game->t_wall)
        ft_printf("fuck");
    game->t_collect = mlx_xpm_file_to_image(game->mlx, "textures/collectable.xpm", 
    &i_w, &i_h);
    if (i_w != SIZE || i_h != SIZE || !game->t_collect)
        ft_printf("fuck");
}

void make_map(t_gdata *game)
{
    int i;
    int j;

    j = -1;
    while (++j < 2)
    {
        i = -1;
        while (++i < 5)
        {
            usleep(50000);
            if (i == 0)
                mlx_put_image_to_window(game->mlx, game->win, game->t_player, i * SIZE, j * SIZE);
            else if (i == 1)
                mlx_put_image_to_window(game->mlx, game->win, game->t_wall, i * SIZE, j * SIZE);
            else if (i == 2)
                mlx_put_image_to_window(game->mlx, game->win, game->t_collect, i * SIZE, j * SIZE);
            else if (i == 3)
                mlx_put_image_to_window(game->mlx, game->win, game->t_exit, i * SIZE, j * SIZE);
            else if (i == 4)
                mlx_put_image_to_window(game->mlx, game->win, game->t_floor, i * SIZE, j * SIZE);
        }
    }
}

void clean_img(t_gdata *game)
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

int close_game(int key, t_gdata *game)
{
    ft_printf(" HEYYYYYYYYYY %d\n", key);
    if (key == 65307)
    {
        mlx_destroy_window(game->mlx, game->win);
        clean_img(game);
        mlx_loop_end(game->mlx);
        mlx_destroy_display(game->mlx);
        free(game->mlx);
    }
    exit(EXIT_SUCCESS);
    return (0);
}

void init_game(t_gdata *game)
{
    int width;
    int height;

    width = 5 * SIZE;
    height = 2 * SIZE;
    game->mlx = mlx_init();
    usleep(50000);
    game->win = mlx_new_window(game->mlx, width, height, "so_long");
    usleep(50000);
    init_textures(game);
    //load_map(game);
    make_map(game);
    mlx_hook(game->win, 02, 1L<<0, close_game, game);
    mlx_loop(game->mlx);
}



int main(void)
{
    t_gdata test;
    init_game(&test);
}