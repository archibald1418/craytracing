NAME	= window
LIBFT	= ./libft
LIBA	= $(LIBFT)/libft.a
MLX		= minilibx_mms_20200219
MLXLL	= $(MLX)/libmlx.dylib
CC		= gcc
INCL	= ./includes
CFLAGS	= -Wall -Wextra -Werror
TESTDIR = ./tests

HFILES	=	colors.h \
			conf.h \
			minirt.h \
			shapes.h \
			parser.h \
			vectors.h \
			utils.h

SRCS	= 	colors.c \
			conf.c \
			vectors.c \
			utils.c \
			parser.c \
			parser_utils.c \
			infobar.c \
			ft_strsplit.c \
			ft_atof.c \
			rays.c \
			camera.c \
			checkers.c \
			setters.c \
			tracers.c \
			intersects.c \
			render.c \
			lights.c \
			normals.c \
			matrix_utils.c

DIR			=	srcs/
HEADERS		=	$(addprefix $(INCL)/, $(HFILES))
SOURCE		=	$(addprefix ./srcs/, $(SRCS))
IFLAG		=	-I$(INCL) -I./$(MLX) -I$(LIBFT)
FRM			=	-framework OpenGL -framework AppKit
LIBAS		= 	$(MLXLL) $(LIBA)
OBJ			=	${SOURCE:.c=.o}

all: $(NAME)

$(LIBA):
	make bonus -j4 -C libft
	cp $(LIBA) ./

$(MLXLL): $(LIBA)
	make -C ./$(MLX)
	cp $(MLXLL) ./

clean:
	make clean -C $(LIBFT)
	make clean -C $(MLX)
	rm -rf $(OBJ) *.out *.dSYM

fclean: clean
	make fclean -C $(LIBFT)
	rm -rf ./*.a ./*.dylib a.out $(NAME)

$(NAME): $(MLXLL) $(OBJ) $(HEADERS)
	$(CC) -g main.c  $(LIBAS) $(SOURCE) $(IFLAG) $(FRM) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -g $(IFLAG) -c $< -o $@

test-colors:
	$(CC) $(TESTDIR)/colors_test.c $(TESTDIR)/infobar.c $(SOURCE) $(LIBAS) -g $(IFLAG) -I $(TESTDIR) $(FRM) -o $(NAME)

test-line: 
	$(CC) $(TESTDIR)/line_test.c $(TESTDIR)/infobar.c $(SOURCE) $(LIBAS) -g $(IFLAG) -I $(TESTDIR) $(FRM) -o $(NAME)
test-triangle:
	$(CC) $(TESTDIR)/triangle_test.c $(TESTDIR)/infobar.c $(SOURCE) $(LIBAS) -g $(IFLAG) -I $(TESTDIR) $(FRM) -o $(NAME)

test-window:
	$(CC) main.c $(SOURCE) -g $(IFLAG) $(LIBAS) $(FRM) -o $(NAME)

test-atof: $(MLXLL)
	gcc $(TESTDIR)/ft_atof_test.c $(SOURCE) $(LIBA) -g $(IFLAG) -I $(TESTDIR)  $< -o atof

test-parser: $(MLXLL) $(HEADERS)
	gcc -g  $(LIBA) $(IFLAG) -I$(TESTDIR)  -o parser \
	$(TESTDIR)/parser_test.c $(TESTDIR)/test_funcs.c \
	$(LIBFT)/*.c \
	srcs/setters.c \
	srcs/checkers.c \
	srcs/parser.c \
	srcs/parser_utils.c \
	srcs/ft_strsplit.c \
	srcs/ft_atof.c \
	srcs/camera.c \
	srcs/vectors.c

test-vectors: $(MLXLL) $(LIBA)
	$(CC) $(TESTDIR)/vectors_test.c $(TESTDIR)/infobar.c $(SOURCE) $(LIBAS) -g $(IFLAG) -I $(TESTDIR) $(FRM) -o $(NAME)

test-rays: $(MLXLL) $(LIBA)
	$(CC) $(TESTDIR)/rays_test.c $(SOURCE) $(LIBAS) -g $(IFLAG) -I $(TESTDIR) $(FRM) -o $(NAME)

re: fclean all

.PHONY: fclean clean all
