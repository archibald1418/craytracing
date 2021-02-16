LIB = libft/libft.a

all: liba

liba:
	make -C libft
	cp $(LIB) ./

fclean:
	make fclean -C libft
	rm -rf libft.a

clean:
	make clean -C libft

re: clean fclean all