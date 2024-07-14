#include <so_long.h>

void clean_maps(t_map *map)
{
    int i;
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

void map_error(const char *str, t_map *map)
{
    ft_printf("Error\n%s\n", str);
    if (map->fd != -1)
        close(map->fd);
    clean_maps(map);
    exit(EXIT_FAILURE);
}

void check_rectangle(t_map *map, char *line)
{
    char *aux;

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

void get_dimensions(t_map *map)
{
    char *line;
    char *aux;

    line = get_next_line(map->fd);
    if (!line)
        map_error("map is empty", map);
    map->width = ft_strlen(line) - 1;
    check_rectangle(map, line);
    map->map = (char **)malloc(sizeof(char *) * (map->height + 1));
    map->map[map->height] = '\0';
    close(map->fd);
}


void readmap(char *path, t_map *map)
{
    int i;
    char *newstr;
    char *line;

    map->fd = open(path, O_RDONLY);
    if (map->fd == -1)
        map_error("Error opening file, file might not exist", map);
    newstr = ft_strrchr(path, '.');
    if (ft_strncmp(newstr, ".ber", 5) != 0)
        map_error("Bad extension. Maps should have \".ber\" extension", map);
    i = -1;
    get_dimensions(map);
    map->fd = open(path, O_RDONLY);
    while (++i < map->height)
    {
        line = get_next_line(map->fd);
        map->map[i] = ft_substr(line, 0, map->width);
        free(line);
    }
    close(map->fd);
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

void init_map(t_map *map)
{
    map->height = 0;
    map->width = 0;
    map->map = NULL;
	map->copy = NULL;
	map->collectable = 0;
	map->exit = 0;
	map->player = 0;
}

void check_chars(t_map *map, char *line)
{
	int i;

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
			if (ft_strchr(map->copy[i], 'C'))
				map_error("theres at least one unreachable collectable!", map);
			if (ft_strchr(map->copy[i], 'E'))
				map_error("unreachable exit!", map);
		}
	}
}

void fill_map(t_map *map)
{
	int i;
	int j;
	
	j = -1;
	while (map->copy[++j])
	{
		i = -1;
		while (map->copy[j][++i])
		{
			if (map->copy[j][i] == '0' || map->copy[j][i] == 'C'
			|| map->copy[j][i] == 'E')
			{
				if (map->copy[j][i + 1] == 'P' || map->copy[j][i - 1] == 'P' ||
				map->copy[j + 1][i] == 'P' || map->copy[j - 1][i] == 'P')
				{
					map->copy[j][i] = 'P';
					fill_map(map);
				}
			}
		}
	}
}

void valid_check(t_map *map)
{
    int i;
	int c;
	int e;

    i = -1;
    while(map->map[++i])
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
		map->copy[i] = '\0';
	c = map->collectable;
	e = map->exit;
	fill_map(map);
	check_chars(map, "");
	print_map(map->copy);
}

//ARREGLAR MAP-map_ERROR