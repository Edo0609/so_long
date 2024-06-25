NAME = so_long

CC = gcc

#CFLAGS = -Wall -Werror -Wextra -Iincludes -Imlx_linux
CFLAGS = -Iincludes -Imlx_linux

MLXFLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -Imlx_linux -Llibft -lftprintf -lXext -lX11 -lm -lz

SRC = map_parse.c

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
	