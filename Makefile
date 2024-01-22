CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_LIBFT = libft/ft_isalpha.c libft/ft_isdigit.c libft/ft_isalnum.c libft/ft_isascii.c libft/ft_strlen.c \
	   libft/ft_toupper.c libft/ft_tolower.c libft/ft_strchr.c libft/ft_strrchr.c libft/ft_strncmp.c \
	   libft/ft_strnstr.c libft/ft_strlcpy.c libft/ft_strlcat.c libft/ft_atoi.c libft/ft_strdup.c \
	   libft/ft_substr.c libft/ft_strjoin.c libft/ft_split.c libft/ft_itoa.c libft/ft_strmapi.c \
	   libft/ft_putchar_fd.c libft/ft_putstr_fd.c libft/ft_putendl_fd.c libft/ft_isprint.c \
	   libft/ft_putnbr_fd.c libft/ft_strtrim.c libft/ft_memcpy.c libft/ft_memmove.c libft/ft_memset.c \
	   libft/ft_memcmp.c libft/ft_memchr.c libft/ft_bzero.c libft/ft_calloc.c libft/ft_striteri.c \
	   libft/get_next_line_utils.c libft/get_next_line.c

SRC = pipex.c

SRC_UTILS = utils.c utils2.c

OBJ = $(SRC:.c=.o)
OBJ_LIBFT = $(SRC_LIBFT:.c=.o)
LIBFT = libft/libft.a
NAME = pipex

all: $(NAME)

$(NAME): $(OBJ_LIBFT) $(SRC) $(SRC_UTILS)
	$(CC) $(CFLAGS) $(SRC) $(SRC_UTILS) $(LIBFT) -o $(NAME)

%.o: %.c
	$(MAKE) -C libft

clean:
	rm -f $(OBJ)
	$(MAKE) -C libft clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all

.PHONY: all bonus clean fclean re