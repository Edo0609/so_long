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

typedef struct s_map
{
    int fd;
    char **map;
    char **copy;
    int width;
    int height;
    int collectable;
    int exit;
    int player;
}   t_map;

typedef struct s_gdata
{
    void    *mlx;
    void    *win;

    void    *img;
    char    *addr;
    int     bpp;
    int     ll;
    int     endian;

    void    *t_player;
    void    *t_floor;
    void    *t_wall;
    void    *t_exit;

    int x_pos;
    int y_pos;

    t_map map;
}   t_gdata;

void get_dimensions(t_map *map);
void readmap(char *path, t_map *map);
void map_error(const char *str, t_map *map);
void init_map(t_map *map);
void clean_maps(t_map *map);
void check_rectangle(t_map *map, char *line);
void check_line(char *line, char *chars, t_map *map);
void check_borders_and_tiles(t_map *map);
void print_map(char **map);
void valid_check(t_map *map);
void check_chars(t_map *map, char *line);
void fill_map(t_map *map);



#endif