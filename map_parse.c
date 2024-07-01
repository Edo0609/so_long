#include <so_long.h>

void error(const char *str)
{
    perror(str);
    exit(EXIT_FAILURE);
}

void get_dimensions(t_map *map)
{
    char *line;

    line = get_next_line(map->fd);
    map->height = 0;
    map->width = ft_strlen(line);
    if (!line)
        error("map is empty");
    while (line)
    {
        line = get_next_line(map->fd);
        if (line && (ft_strlen(line) != map->width))
            error("map is not rectangular");
        map->height++;
    }
    map->map = (char **)malloc(sizeof(char *) * (map->height + 1));
}

void readmap(char *path)
{
    t_map map;
    int i;

    i = 0;
    map.fd = open(path, O_RDONLY);
    if (map.fd == -1)
        error("Error opening file");
    get_dimensions(&map);
    map.map[i] = get_next_line(map.fd);
    while (i < map.height)
    {
        map.map[i] = get_next_line(map.fd);
        i++;
    }

    
}

int main(int ac, char **av)
{
    if (ac != 2)
    {
        ft_printf("invalid format. Format: ./so_long [MAP]");
        return (1);
    }
        readmap(av[1]);
    return (0);
}