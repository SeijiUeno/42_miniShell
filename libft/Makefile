# Makefile for Libft Library

# Compiler and Flags
CC      = gcc
CFLAGS  = -Wall -Wextra -Werror

# Target and Directories
NAME    = libft.a
SRC_DIR = src
OBJ_DIR = obj

# Source and Object Files
SRC_FILES = ft_isdigit.c ft_strlen.c ft_atoi.c ft_putnbr.c \
            ft_strcmp.c ft_substr.c ft_memcpy.c ft_strdup.c \
            ft_strlcpy.c ft_calloc.c ft_bzero.c ft_putchar_fd.c \
            ft_putstr_fd.c ft_putendl_fd.c ft_strncmp.c \
            garbage_collector.c

OBJ_FILES = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Rules
.PHONY: all clean fclean re

all: $(NAME)

# Build the library
$(NAME): $(OBJ_FILES)
	@ar rcs $(NAME) $(OBJ_FILES)
	@echo "Created $(NAME)"

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled $< -> $@"

# Create object directory if it doesn't exist
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "Created directory: $(OBJ_DIR)"

# Clean object files
clean:
	@rm -rf $(OBJ_DIR)
	@echo "Cleaned object files"

# Full clean (object files and library)
fclean: clean
	@rm -f $(NAME)
	@echo "Removed $(NAME)"

# Rebuild everything
re: fclean all
