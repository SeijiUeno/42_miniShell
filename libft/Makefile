# Variables
NAME = libft.a
CC = gcc
CFLAGS = -Wall -Werror -Wextra
OBJ_DIR = obj/
SRC_DIR = src/

SOURCES = \
	ft_isdigit.c \
	ft_strlen.c \
	ft_atoi.c \
	ft_putnbr.c \
	ft_strcmp.c \
	ft_substr.c \
	ft_memcpy.c \
	ft_strdup.c \
	ft_strlcpy.c \
	ft_calloc.c \
	ft_bzero.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_strncmp.c 

OBJECTS = $(addprefix $(OBJ_DIR), $(SOURCES:.c=.o))
SRC = $(addprefix $(SRC_DIR), $(SOURCES))

.PHONY: all clean fclean re

all: $(OBJ_DIR) $(NAME)

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(NAME): $(OBJECTS)
	ar rcs $(NAME) $(OBJECTS)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all
