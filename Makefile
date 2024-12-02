# Makefile for Minishell Project (with Colors)

# Compiler and Flags
CC       = gcc
CFLAGS   = -Iinclude -Isrc/token -Ilibft
READLINE = -lreadline

# Colors
GREEN    = \033[32m
YELLOW   = \033[33m
BLUE     = \033[34m
RED      = \033[31m
RESET    = \033[0m

# Target and Directories
NAME     = Minishell
SRC_DIR  = src
OBJ_DIR  = objects
LIBFT_DIR = libft
LIBFT    = $(LIBFT_DIR)/libft.a

# Source and Object Files
SRC_FILES = signal/signals.c \
			error/error.c \
            token/generate_tokens.c \
            token/operator_tokens.c \
            token/quoted_tokens.c \
            token/token_utils.c \
			token/validate_tokens.c \
            ast/ast.c \
            buildins/echo.c \
            buildins/pwd.c \
			buildins/unset.c \
			buildins/export.c \
			buildins/env.c \
			buildins/cd.c \
			env/get_env.c \
			env/path_holders.c \
			main.c

SRCS      = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS      = $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRCS))

# Rules
.PHONY: all clean fclean re

all: $(NAME)

# Build the executable
$(NAME): $(OBJS) $(LIBFT)
	@echo "$(BLUE)Linking objects and building executable: $(NAME)$(RESET)"
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(READLINE)
	@echo "$(GREEN)Executable $(NAME) created successfully!$(RESET)"

# Compile source files into object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling $< -> $@$(RESET)"
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

# Build libft library
$(LIBFT):
	@echo "$(BLUE)Building libft library...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR)
	@echo "$(GREEN)Libft library built successfully!$(RESET)"

# Create object directory if it doesn't exist
$(OBJ_DIR):
	@echo "$(BLUE)Creating directory: $(OBJ_DIR)$(RESET)"
	@mkdir -p $(OBJ_DIR)

# Clean object files
clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@$(MAKE) -C $(LIBFT_DIR) clean

# Full clean (object files, library, and executable)
fclean: clean
	@echo "$(RED)Removing executable $(NAME) and cleaning libft...$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

# Rebuild everything
re: fclean all
