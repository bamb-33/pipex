CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = mandatory/pipex.c utlis.c

SRC_B = bonus/pipex_bonus.c utlis.c

OBJ = $(SRC:.c=.o)
OBJ_B = $(SRC_B:.c=.o)
LIBFT = libft.a
NAME = pipex
BONUS = pipex_b

all: $(NAME)

bonus: $(BONUS)

$(LIBFT):
	$(MAKE) -C libft

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ) libft/libft.a -o $(NAME)

bonus: $(OBJ_B) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJ_B) libft/libft.a -o $(BONUS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJ_B)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME) $(BONUS)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all bonus clean fclean re