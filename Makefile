NAME	= window
LIBA	= libft/libft.a
LIBFT	= ./libft
MLX		= minilibx_mms_20200219
MLXLL	= $(MLX)/libmlx.dylib
CC		= gcc
INCL	= ./includes
CFLAGS	= -Wall -Wextra -Werror
TESTDIR = ./tests

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
			triangle.c \
			vectors.c \
			utils.c

DIR			=	srcs/
HEADERS		=	$(addprefix $(INCL)/, $(HFILES))
SOURCE		=	$(addprefix ./srcs/, $(SRCS))
IFLAG		=	-I $(INCL) -I $(MLX) -I $(LIBFT)
FRM			=	-framework OpenGL -framework AppKit
LIBAS		= 	$(MLXLL) $(LIBA)

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
	$(CC) main.c $(SOURCE) $(LIBAS) $(IFLAG) $(FRM) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -I $(HEADERS) -c $< -o $@

test-colors:
	$(CC) $(TESTDIR)/colors_test.c $(TESTDIR)/infobar.c $(SOURCE) $(LIBAS) -g $(IFLAG) -I $(TESTDIR) $(FRM) -o $(NAME)

test-line: 
	$(CC) $(TESTDIR)/line_test.c $(TESTDIR)/infobar.c $(SOURCE) $(LIBAS) -g $(IFLAG) -I $(TESTDIR) $(FRM) -o $(NAME)
test-triangle:
	$(CC) $(TESTDIR)/triangle_test.c $(TESTDIR)/infobar.c $(SOURCE) $(LIBAS) -g $(IFLAG) -I $(TESTDIR) $(FRM) -o $(NAME)

test-window:
	$(CC) main.c $(SOURCE) -g $(IFLAG) $(LIBAS) $(FRM) -o $(NAME)

re: clean fclean all

.PHONY: fclean clean all
