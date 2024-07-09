#include <so_long.h>

void clean_all(t_map *map)
{
    int i;
    if (map->map)
    {
        i = -1;
        while (map->map[++i])
            free(map->map[i]);
        free(map->map);
    }
}

void error(const char *str, t_map *map)
{
    ft_printf("Error\n%s\n", str);
    if (map->fd != -1)
        close(map->fd);
    clean_all(map);
    ft_printf("%d", map->fd);
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
            aux = ft_substr(line, 0, map->width);
            if (ft_strlen(aux) != map->width)
            {
                free(line);
                free(aux);
                error("map is not rectangular", map);
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
        error("map is empty", map);
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
        error("Error opening file, file might not exist", map);
    newstr = ft_strrchr(path, '.');
    if (ft_strncmp(newstr, ".ber", 5) != 0)
        error("Bad extension. Maps should have \".ber\" extension", map);
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
        error("The map must be walled off!", map);
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
        error("Invalid character. Valid characters: 1, 0, P, E, C", map);
    if (line[i])
        error("The map must be walled off!", map);
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

void print_map(t_map *map)
{
    int i;

    i = -1;
    while(map->map[++i])
        ft_printf("%s\n", map->map[i]);
}

void init_map(t_map *map)
{
    map->height = 0;
    map->width = 0;
    map->map = NULL;
}

int main(int ac, char **av)
{
    t_map   map;

    init_map(&map);
    if (ac != 2)
    {
        error("invalid format. Format: ./so_long [MAP]", &map);
        return (1);
    }
        ft_printf("for leaks, use the command: valgrind --leak-check=full --show-leak-kinds=all ./so_long %s\n", av[1]);
        readmap(av[1], &map);
        check_borders_and_tiles(&map);
        print_map(&map);
        clean_all(&map);
    return (0);
}