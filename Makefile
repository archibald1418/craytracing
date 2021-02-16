LIB	=	libft/libft.a
CC	=	gcc
INCLUDES	=	./includes

all: liba

liba:
	make -C libft
	cp $(LIB) ./

fclean:
	make fclean -C libft
	rm -rf libft.a

clean:
	make clean -C libft

test-colors:
	$(CC) -I $(INCLUDES) colors_test.c; ./a.out

re: clean fclean all