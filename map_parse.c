#include <so_long.h>

typedef struct s_map
{
    int fd;
    int width;
    int height;
    int collectable;
    int exit;
    int player;
}   t_map;

void readmap(char *path)
{
    t_map map;

    map.fd = open(path, O_RDONLY);
    
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