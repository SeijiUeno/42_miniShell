# Makefile for Minishell Project

# Compiler and Flags
CC       = gcc
CFLAGS   = -Wall -Wextra -Werror -Iinclude -Isrc/token -Ilibft
READLINE = -lreadline

# Target and Directories
NAME     = Minishell
SRC_DIR  = src
OBJ_DIR  = objects
LIBFT_DIR = libft
LIBFT    = $(LIBFT_DIR)/libft.a

# Source and Object Files
SRC_FILES = main.c \
            signal/signals.c \
            token/tokenizer.c \
            token/word_token.c \
            token/operator_token.c \
            token/auxiliary.c \
            ast/ast.c \
            buildins/echo.c \
            buildins/pwd.c

SRCS      = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS      = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Rules
.PHONY: all clean fclean re

all: $(NAME)

# Build the executable
$(NAME): $(OBJS) $(LIBFT)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(READLINE)
	@echo "Created executable: $(NAME)"

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled $< -> $@"

# Build libft library
$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)
	@echo "Built libft library"

# Create object directory if it doesn't exist
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "Created directory: $(OBJ_DIR)"

# Clean object files
clean:
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "Cleaned object files"

# Full clean (object files, library, and executable)
fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "Removed $(NAME)"

# Rebuild everything
re: fclean all
