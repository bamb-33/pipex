CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = mandatory/pipex.c utlis.c

SRC_B = bonus/pipex_bonus.c utlis.c

OBJ = $(SRC:.c=.o)
OBJ_B = $(SRC_B:.c=.o)
NAME = pipex
BONUS = pipex_b

all: $(NAME)
bonus: $(BONUS)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) libft/libft.a -o $(NAME)

$(BONUS): $(OBJ_B)
	$(CC) $(CFLAGS) $(OBJ_B) libft/libft.a -o $(BONUS)

%.o: %.c
	$(MAKE) -C libft
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJ_B)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME) $(BONUS)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all bonus clean fclean re