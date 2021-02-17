NAME	= window
LIBA	= libft/libft.a
MLX		= minilibx_mms_20200219
MLXLL	= $(MLX)/libmlx.dylib
CC		= gcc
INCL	= ./includes
CFLAGS	= -Wall -Wextra -Werror

all: $(NAME)

$(LIBA):
	make -j4 -C libft
	cp $(LIBA) ./

$(MLXLL): $(LIBA)
	make -C ./$(MLX)
	cp $(MLXLL) ./

clean:
	make clean -C libft
	make clean -C $(MLX)

fclean:
	make fclean -C libft
	rm -rf libft.a

$(NAME): $(MLXLL) $(OBJ)
	$(CC) main.c -I $(INCL) $(LIBA) $(MLXLL) -framework OpenGL -framework AppKit -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I $(INCL) -c $< -o $@

test-colors:
	$(CC) -I $(INCLUDES) colors_test.c; ./a.out

test-window:
	$(CC) main.c -I $(INCL) $(LIBA) $(MLXLL) -framework OpenGL -framework AppKit -o $(NAME)

re: clean fclean all

.PHONY: fclean clean all