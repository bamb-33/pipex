CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = mandatory/pipex.c utlis.c

SRC_B = bonus/pipex_bonus.c utlis.c

OBJ = $(SRC:.c=.o)
OBJ_B = $(SRC_B:.c=.o)
NAME = pipex.a
BONUS = pipex_b.a

all: $(NAME)
bonus: $(BONUS)

$(NAME): $(OBJ)
	ar -rcs $(NAME) $(OBJ)
	cc mandatory/pipex.c libft/libft.a pipex.a -o pipex

$(BONUS): $(OBJ_B)
	ar -rcs $(BONUS) $(OBJ_B)
	cc bonus/pipex_bonus.c libft/libft.a pipex_b.a -o pipex

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