NAME = gnl
LIBS = ./libftest.a ./libft.a
INCLUDES = ./libft.h ./tests.h ./get_next_line.h
TESTS = ./tests.c

SRCS =	../get_next_line.c ../get_next_line_utils.c
INCLUDES = ../get_next_line.h

CC = gcc
CFLAGS = -Werror -Wall -Wextra
all: $(NAME) $(TESTS)
$(NAME): $(INCLUDES)
	# Trying to read from user input
	read -p "Input buffer size :-> " BUFSIZ && \
	$(CC) $(CFLAGS) -D BUFFER_SIZE=$$BUFSIZ $(SRCS) $(TESTS) -o $(NAME)

test-lists: libft.a $(TESTS)
	$(CC) -g -L. -lft lists_main.c -o tests
	./tests 

fclean: $(NAME)
	rm -rf $(NAME)
re: fclean all

.PHONY: all clean fclean re test