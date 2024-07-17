/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: epenaloz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 18:16:18 by epenaloz          #+#    #+#             */
/*   Updated: 2024/07/15 18:16:19 by epenaloz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <so_long.h>

void	check_chars(t_map *map, char *line)
{
	int	i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == 'C')
			map->collectable++;
		else if (line[i] == 'P')
			map->player++;
		else if (line[i] == 'E')
			map->exit++;
	}
	if (map->copy)
	{
		i = -1;
		while (map->copy[++i])
		{
			if (ft_strchr(map->copy[i], 'C') || ft_strchr(map->copy[i], 'E'))
				map_error("The map is unbeatable!", map);
		}
	}
}

void	fill_map(t_map *map)
{
	int	i;
	int	j;

	j = -1;
	while (map->copy[++j])
	{
		i = -1;
		while (map->copy[j][++i])
		{
			if (map->copy[j][i] == '0' || map->copy[j][i] == 'C'
			|| (map->copy[j][i] == 'E' && map->copy_collect == 0))
			{
				if (map->copy[j][i + 1] == 'P' || map->copy[j][i - 1] == 'P' ||
				map->copy[j + 1][i] == 'P' || map->copy[j - 1][i] == 'P')
				{
					if (map->copy[j][i] == 'C')
						map->copy_collect--;
					map->copy[j][i] = 'P';
					fill_map(map);
				}
			}
		}
	}
}

void	valid_check(t_map *map)
{
	int	i;

	i = -1;
	while (map->map[++i])
		check_chars(map, map->map[i]);
	if (map->player > 1 || map->player == 0)
		map_error("there must be exactly one player!", map);
	if (map->exit > 1 || map->exit == 0)
		map_error("there must be exactly one exit!", map);
	if (map->collectable < 1)
		map_error("there must be at least one collectable!", map);
	map->copy = (char **)malloc(sizeof(char *) * (map->height + 1));
	i = -1;
	while (map->map[++i])
		map->copy[i] = ft_strdup(map->map[i]);
	map->copy[i] = NULL;
	map->copy_collect = map->collectable;
	fill_map(map);
	check_chars(map, "");
}

void	get_dimensions(t_map *map)
{
	char	*line;

	line = get_next_line(map->fd);
	while (line && line[0] == '\n')
	{
		free(line);
		line = get_next_line(map->fd);
		map->start++;
	}
	if (!line)
		map_error("map is empty", map);
	if (ft_strchr(line, '\n'))
		map->width = ft_strlen(line) - 1;
	else if (line)
		map->width = ft_strlen(line);
	check_rectangle(map, "", line);
	if ((map->width < 3 && map->height > 2)
		|| (map->height < 3 && map->width > 2))
		map_error("Map is too small!", map);
	map->map = (char **)malloc(sizeof(char *) * (map->height + 1));
	map->map[map->height] = '\0';
	close(map->fd);
}

void	readmap(char *path, t_map *map)
{
	size_t	i;
	char	*newstr;
	char	*line;

	map->fd = open(path, O_RDONLY);
	if (map->fd == -1)
		map_error("Error opening file, file might not exist", map);
	newstr = ft_strrchr(path, '.');
	if (ft_strncmp(newstr, ".ber", 5) != 0)
		map_error("Bad extension. Maps should have \".ber\" extension", map);
	i = -1;
	get_dimensions(map);
	map->fd = open(path, O_RDONLY);
	line = get_next_line(map->fd);
	while (line && (++i) < map->height + map->start)
	{
		if (line[0] != '\n')
			map->map[i - map->start] = ft_substr(line, 0, map->width);
		free(line);
		line = get_next_line(map->fd);
	}
	free_gnl(&line, map);
	close(map->fd);
}
