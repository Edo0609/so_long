/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epenaloz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 19:42:49 by epenaloz          #+#    #+#             */
/*   Updated: 2024/01/26 19:43:43 by epenaloz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "libft.h"
# include "ft_printf.h"
# include "get_next_line.h"
# include <mlx.h>
# include <errno.h>
# include <stdio.h>

# define SIZE 128

# define W_KEY 119
# define A_KEY 97
# define S_KEY 115
# define D_KEY 100
# define UP 65362
# define LEFT 65361
# define DOWN 65364
# define RIGHT 65363

# define ESC 65307

typedef struct s_map
{
    int fd;
    char **map;
    char **copy;
    size_t width;
    size_t height;
    int collectable;
    int exit;
    int player;
}   t_map;

typedef struct s_gdata
{
    void    *mlx;
    void    *win;

    void    *t_player;
    void    *t_floor;
    void    *t_wall;
    void    *t_exit;
    void    *t_collect;

    int x_pos;
    int y_pos;
    int c;
    int moves;
    int exit_x;
    int exit_y;

    t_map map;
}   t_gdata;

void clean_maps(t_map *map);
void map_error(const char *str, t_map *map);
void end_game(char *str, int status, t_gdata *game);
void destroy_textures(t_gdata *game);

void check_rectangle(t_map *map, char *aux, char *line);
void check_line(char *line, char *chars, t_map *map);
void check_borders_and_tiles(t_map *map);
void print_map(char **map);

void get_dimensions(t_map *map);
void readmap(char *path, t_map *map);
void check_chars(t_map *map, char *line);
void valid_check(t_map *map);
void fill_map(t_map *map);

void init_game(t_gdata *game);
void init_map(t_map *map);

int keypress(int key, t_gdata *game);
int close_win(t_gdata *game);
void check_movement(int new_x, int new_y, t_gdata *game);

void load_map(t_gdata *game);
void put_image(int x, int y, char texture, t_gdata *game);
void init_textures(t_gdata *game);
void load_texture(void **texture, char *path, t_gdata *game);


#endif