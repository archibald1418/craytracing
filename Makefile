NAME	= window
LIBFT	= ./libft
LIBA	= $(LIBFT)/libft.a
GNL		= ./gnl
GNLA	= $(GNL)/gnl.a
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

SRCS	= 	circle.c \
			colors.c \
			conf.c \
			line.c \
			square.c \
			triangle.c \
			vectors.c \
			utils.c \
			parser.c \
			parser_utils.c \
			ft_strsplit.c \
			ft_atof.c

DIR			=	srcs/
HEADERS		=	$(addprefix $(INCL)/, $(HFILES))
SOURCE		=	$(addprefix ./srcs/, $(SRCS))
IFLAG		=	-I $(INCL) -I $(MLX) -I $(LIBFT) -I $(GNL)
FRM			=	-framework OpenGL -framework AppKit
LIBAS		= 	$(MLXLL) $(LIBA) $(GNLA)

all: $(NAME)

$(LIBA):
	make bonus -j4 -C libft
	cp $(LIBA) ./

$(GNLA):
	make -C $(GNL)
	cp $(GNLA) ./

$(MLXLL): $(LIBA) $(GNLA)
	make -C ./$(MLX)
	cp $(MLXLL) ./

clean:
	make clean -C $(LIBFT)
	make clean -C $(MLX)
	make clean -C $(GNL)
	rm -rf *.o *.out *.dSYM

fclean: clean
	make fclean -C $(LIBFT)
	make fclean -C $(GNL)
	rm -rf ./*.a ./*.dylib a.out $(NAME)

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

test-gnl: $(GNLA)
	$(CC) $(TESTDIR)/gnl_test.c -g $(IFLAG) -I $(TESTDIR) $(FRM) $< -o gnl.o

test-atof: $(MLXLL)
	gcc $(TESTDIR)/ft_atof_test.c $(SOURCE) $(LIBA) -g $(IFLAG) -I $(TESTDIR)  $< -o atof

test-parser: $(LIBA) $(GNLA)
	gcc -g $(TESTDIR)/parser_test.c $(TESTDIR)/test_funcs.c srcs/parser.c srcs/parser_utils.c srcs/ft_strsplit.c $(LIBA) $(GNLA) $(IFLAG) -I $(TESTDIR) -o parser

re: fclean all

.PHONY: fclean clean all gnl
