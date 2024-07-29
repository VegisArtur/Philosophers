CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra -g -pthread
NAME		=	philosophers
SRC			=	main.c		initialization.c	utils.c			life.c	\
				monitor.c	error_and_free.c	thread_loop.c
OBJ			=	$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: clean all

.PHONY: all clean fclean re
