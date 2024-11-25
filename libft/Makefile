# Makefile for Libft Library (with Colors)

# Compiler and Flags
CC      = gcc
CFLAGS  = -Wall -Wextra -Werror

# Colors
GREEN   = \033[32m
YELLOW  = \033[33m
BLUE    = \033[34m
RED     = \033[31m
RESET   = \033[0m

# Target and Directories
NAME    = libft.a
SRC_DIR = src
OBJ_DIR = obj

# Source and Object Files
SRC_FILES = ft_isdigit.c ft_strlen.c ft_atoi.c ft_putnbr.c \
            ft_strcmp.c gc_substr.c ft_memcpy.c gc_strdup.c \
            ft_strlcpy.c ft_calloc.c ft_bzero.c ft_putchar_fd.c \
            ft_putstr_fd.c ft_putendl_fd.c ft_strncmp.c \
            garbage_collector.c ft_error.c gc_strndup.c \
			ft_isalpha.c ft_strchr.c ft_isalnum.c

OBJ_FILES = $(patsubst %.c,$(OBJ_DIR)/%.o,$(SRC_FILES))

# Rules
.PHONY: all clean fclean re

all: $(NAME)

# Build the library
$(NAME): $(OBJ_FILES)
	@echo "$(BLUE)Creating library: $(NAME)$(RESET)"
	@ar rcs $(NAME) $(OBJ_FILES)
	@echo "$(GREEN)Library $(NAME) created successfully!$(RESET)"

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling $< -> $@$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

# Create object directory if it doesn't exist
$(OBJ_DIR):
	@echo "$(BLUE)Creating directory: $(OBJ_DIR)$(RESET)"
	@mkdir -p $(OBJ_DIR)

# Clean object files
clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)

# Full clean (object files and library)
fclean: clean
	@echo "$(RED)Removing library $(NAME)...$(RESET)"
	@rm -f $(NAME)

# Rebuild everything
re: fclean all
