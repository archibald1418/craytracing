NAME	= miniRT
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
			colors_bits.c \
			colors_extra.c \
			conf.c \
			utils.c \
			vectors.c \
			vectors_angles.c \
			vectors_arithmetic.c \
			vectors_products.c \
			vectors_utils.c \
			parser.c \
			parser_points.c \
			parser_set.c \
			parser_shapes.c \
			parser_utils.c \
			checkers_set.c \
			checkers_planes.c \
			checkers_bodies.c \
			checkers_utils.c \
			ft_strsplit.c \
			ft_atof.c \
			ft_atof_utils.c \
			rays.c \
			camera.c \
			setters.c \
			tracers.c \
			intersects.c \
			intersects_planes.c \
			intersects_bodies.c \
			render.c \
			lights.c \
			lights_phong.c \
			normals.c \
			normals_planes.c \
			normals_bodies.c \
			matrix_utils.c \
			bmp.c \
			rt.c \
			infobar.c

DIR			=	srcs/
HEADERS		=	$(addprefix $(INCL)/, $(HFILES))
SOURCE		=	$(addprefix ./srcs/, $(SRCS)) main.c
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

$(NAME): $(MLXLL) $(OBJ) $(HEADERS) Makefile
	$(CC) -g $(LIBAS) $(SOURCE) libft/*.c $(IFLAG) $(FRM) -fsanitize=address -o $(NAME)

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

test-atof:
	gcc $(TESTDIR)/ft_atof_test.c srcs/ft_atof.c $(LIBA) -g $(IFLAG) -I $(TESTDIR)  $< -o atof

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
