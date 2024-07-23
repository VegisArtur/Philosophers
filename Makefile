CC			=	cc
CFLAGS		=	-Wall -Werror -Wextra -g -pthread
NAME		=	philosophers
SRC			=	main.c	initialization.c
OBJ			=	$(SRC:.c=.o)
LIBFT		=	libft
LIBFT_LIB	=	$(LIBFT)/libft.a

all: $(NAME)

$(NAME): $(OBJ)
	$(MAKE) -C $(LIBFT)
	$(CC) -o $(NAME) $(OBJ) $(LIBFT_LIB)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) -C $(LIBFT) clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT) fclean

re: clean all

.PHONY: all clean fclean re
