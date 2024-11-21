NAME = Minishell

CC = gcc -g
CFLAGS = -Wall -Wextra -Werror -Iinclude -Isrc/token -Ilibft
READLINE = -lreadline

# Source files
SRCS = src/main.c \
       src/signal/signals.c \
       src/token/tokenizer.c \
	   src/token/word_token.c \
	   src/token/operator_token.c \
<<<<<<< HEAD
	   src/token/auxiliary.c \
	   src/parser/ast/ast.c \
	   src/garbage_collector/garbage_collector.c 
=======
	   src/token/auxiliary.c
>>>>>>> main

# Object files directory
OBJ_DIR = objects
OBJS = $(addprefix $(OBJ_DIR)/, $(SRCS:.c=.o))

# Libft library
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# All target
all: $(NAME)

# Build minishell
$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBFT) $(READLINE)

# Build object files in the objects directory
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)/$(dir $<)
	$(CC) $(CFLAGS) -c $< -o $@

# Build libft
$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

# Clean object files
clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean

# Full clean
fclean: clean
	@echo "Removing executable $(NAME)..."
	rm -f $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean

# Rebuild everything
re:	fclean all

.PHONY: all clean fclean re