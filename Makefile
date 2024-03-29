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
			conf_utils.c \
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
			infobar.c \
			main_wrappers.c

DIR			=	srcs/
HEADERS		=	$(addprefix $(INCL)/, $(HFILES))
SOURCE		=	$(addprefix ./srcs/, $(SRCS)) main.c
IFLAG		=	-I$(INCL) -I./$(MLX) -I$(LIBFT)
FRM			=	-framework OpenGL -framework AppKit
LIBAS		= 	$(MLXLL) $(LIBA)
OBJ			=	${SOURCE:.c=.o}

all: libft $(MLXLL) $(NAME)

libft:
	make -j4 -C libft
	# make bonus -j4 -C libft


$(MLXLL):
	make -C ./$(MLX)

clean:
	make clean -C $(LIBFT)
	make clean -C $(MLX)
	rm -rf $(OBJ) *.out *.dSYM

fclean: clean
	make fclean -C $(LIBFT)
	rm -rf ./*.a ./*.dylib a.out $(NAME)

$(NAME): $(OBJ) $(HEADERS) Makefile
	$(CC) -g -L./libft -lft $(MLXLL) $(SOURCE) $(IFLAG) $(FRM) -fsanitize=address -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -g $(IFLAG) -c $< -o $@

re: fclean all

.PHONY: libft fclean clean all
