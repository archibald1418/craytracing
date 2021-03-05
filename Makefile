NAME	= window
LIBA	= libft/libft.a
MLX		= minilibx_mms_20200219
MLXLL	= $(MLX)/libmlx.dylib
CC		= gcc
INCL	= ./includes
CFLAGS	= -Wall -Wextra -Werror

HFILES	=	colors.h \
			conf.h \
			libft.h \
			get_next_line.h \
			libft.h \
			minirt.h \
			mlx.h \
			shapes.h \
			tests.h \
			vectors.h \
			utils.h

SRCS	= 	circle.c \
			colors.c \
			conf.c \
			line.c \
			square.c \
			vectors.c \
			utils.c

DIR		= srcs/
HEADERS		=	$(addprefix $(INCL)/, $(HFILES))
SOURCE		=	$(addprefix ./srcs/, $(SRCS))

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
	rm -rf *.o *.out *.dSYM $(NAME)

fclean:
	make fclean -C libft
	rm -rf libft.a

$(NAME): $(MLXLL) $(OBJ) $(HEADERS)
	$(CC) main.c $(SOURCE) -I $(INCL) $(LIBA) $(MLXLL) -framework OpenGL -framework AppKit -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I $(INCL) -c $< -o $@

test-colors:
	$(CC) -I $(INCL) colors_test.c; ./a.out

test-line:
	$(CC) line_test.c $(SOURCE) -g -I $(INCL) $(LIBA) $(MLXLL) -framework OpenGL -framework AppKit -o $(NAME)

test-window:
	$(CC) main.c $(SOURCE) -g -I $(INCL) $(LIBA) $(MLXLL) -framework OpenGL -framework AppKit -o $(NAME)

re: clean fclean all

.PHONY: fclean clean all
