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

typedef struct s_map
{
    int fd;
    char **map;
    int width;
    int height;
    int collectable;
    int exit;
    int player;
}   t_map;

void get_dimensions(t_map *map);
void readmap(char *path, t_map *map);
void error(const char *str, t_map *map);
void init_map(t_map *map);
void clean_all(t_map *map);
void check_rectangle(t_map *map, char *line);
void check_line(char *line, char *chars, t_map *map);
void check_borders_and_tiles(t_map *map);
void print_map(t_map *map);



#endif
