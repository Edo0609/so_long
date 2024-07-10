#include <so_long.h>


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
        print_map(map.map);
        valid_check(&map);
        clean_all(&map);
    return (0);
}