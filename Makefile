CC = cc
CFLAGS = 

SRC = mandatory/main.c mandatory/strjoin_extra.c mandatory/path_finder.c mandatory/read_file.c\
		mandatory/execute.c mandatory/strs_len.c\
		mandatory/paths/first.c mandatory/paths/second.c mandatory/paths/third.c \
		mandatory/paths/fourth.c mandatory/paths/fifth.c mandatory/paths/sixth.c 

SRC_B = 

OBJ = $(SRC:.c=.o)
OBJ_B = $(SRC_B:.c=.o)
NAME = pipex.a

all: $(NAME)

$(NAME): $(OBJ)
	ar -rcs $(NAME) $(OBJ)
	cc mandatory/main.c libft/libft.a pipex.a -o pipex

%.o: %.c
	$(MAKE) -C libft
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(OBJ_B)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME) $(NAME_BONUS)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all bonus clean fclean re