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
    // if (i_w != SIZE || i_h != SIZE)
        // game_error("textures are not the right size!", game);
    game->t_player = mlx_xpm_file_to_image(game->mlx, "textures/player.xpm", 
    &i_w, &i_h);
    // if (i_w != SIZE || i_h != SIZE)
        // game_error("textures are not the right size!", game);
    game->t_floor = mlx_xpm_file_to_image(game->mlx, "textures/floor.xpm", 
    &i_w, &i_h);
    // if (i_w != SIZE || i_h != SIZE)
        // game_error("textures are not the right size!", game);
    game->t_wall = mlx_xpm_file_to_image(game->mlx, "textures/wall.xpm", 
    &i_w, &i_h);
    // if (i_w != SIZE || i_h != SIZE)
        // game_error("textures are not the right size!", game);
    game->t_collect = mlx_xpm_file_to_image(game->mlx, "textures/collectable.xpm", 
    &i_w, &i_h);
    // if (i_w != SIZE || i_h != SIZE)
        // game_error("textures are not the right size!", game);
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

void init_game(t_gdata *game)
{
    int width;
    int height;

    width = 5 * SIZE;
    height = 2 * SIZE;
    game->mlx = mlx_init();
    game->win = mlx_new_window(game->mlx, width, height, "so_long");
    game->img = mlx_new_image(game->mlx, width, height);
    game->addr = mlx_get_data_addr(game->img, &game->bpp, 
    &game->ll, &game->endian);
    init_textures(game);
    //load_map(game);
    make_map(game);
    mlx_loop(game->mlx);
}



int main(void)
{
    t_gdata test;
    init_game(&test);
}