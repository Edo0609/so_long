NAME = so_long

CC = gcc

CFLAGS = -Wall -Werror -Wextra -Iincludes -Imlx_linux

MLXFLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -Llibft
MLXFLAGS += -lftprintf -lXext -lX11 -lm -lz -g3

SRC = check_map.c game_over.c hooks_and_movement.c load_textures.c \
	  map_utils.c so_long.c

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(MLXFLAGS) -o $(NAME)

clean:
	make clean -C libft 
	rm -f $(OBJ)

fclean: clean
	make fclean -C libft
	rm -f $(NAME)

re: fclean all

libft:
	@make -C libft
	@echo "libft compiled"

.PHONY: all clean fclean re libft
	