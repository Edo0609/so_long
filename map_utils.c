/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epenaloz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:30:18 by epenaloz          #+#    #+#             */
/*   Updated: 2024/07/15 18:30:44 by epenaloz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void check_rectangle(t_map *map, char *aux, char *line)
{
    while (line)
    {
        free(line);
        line = get_next_line(map->fd);
        if (line)
        {
            if (ft_strchr(line, '\n'))
                aux = ft_substr(line, 0, ft_strlen(line) - 1);
            else
                aux = ft_substr(line, 0, ft_strlen(line));
            if (ft_strlen(aux) != map->width)
            {
                while (line)
                {
                    free(line);
                    line = get_next_line(map->fd);
                }
                free(aux);
                map_error("map is not rectangular", map);
            }
            free(aux);
        }
        map->height++;
    }
}

void check_line(char *line, char *chars, t_map *map)
{
    int i;
    int j;

    i = 0;
    j = 0;
    if (line[0] != '1' || line[map->width - 1] != '1')
        map_error("The map must be walled off!", map);
    while (line[i] && chars[j])
    {
        if (line[i] == chars[j])
        {
            j = 0;
            i++;
        }
        else
            j++;
    }
    if (!chars[j] && (chars[0] == '0'))
        map_error("Invalid character. Valid characters: 1, 0, P, E, C", map);
    if (line[i])
        map_error("The map must be walled off!", map);
}

void check_borders_and_tiles(t_map *map)
{
    int i;

    i = 0;

    while (i < map->height)
    {
        if (i == 0 || i == (map->height - 1))
            check_line(map->map[i], "1", map);
        else
            check_line(map->map[i],"01PEC", map);
        i++;
    }
}

void print_map(char **map)
{
    int i;

    i = -1;
    while(map[++i])
        ft_printf("%s\n", map[i]);
}

