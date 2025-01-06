NAME = minishell
.DEFAULT_GOAL := all
.PHONY: all clean fclean re valgrind help
.SILENT:

# **************************************************************************** #
#                                   COLORS                                      #
# **************************************************************************** #

DEFAULT=\033[39m
BLACK=\033[30m
DARK_RED=\033[31m
DARK_GREEN=\033[32m
DARK_YELLOW=\033[33m
DARK_BLUE=\033[34m
DARK_MAGENTA=\033[35m
DARK_CYAN=\033[36m
LIGHT_GRAY=\033[37m
DARK_GRAY=\033[90m
RED=\033[91m
GREEN=\033[92m
ORANGE=\033[93m
BLUE=\033[94m
MAGENTA=\033[95m
CYAN=\033[96m
WHITE=\033[97m
YELLOW = \033[33m
RESET = \033[0m

# **************************************************************************** #
#                                   PATHS                                       #
# **************************************************************************** #

SRCS_PATH = src/
INCS_PATH = includes/ libs/libft/include/
BUILD_DIR := build/
LIBFT_DIR := libs/libft/
GARB_DIR  := libs/garbage_collector/

# **************************************************************************** #
#                                   FILES                                       #
# **************************************************************************** #

SRCS := $(addprefix $(SRCS_PATH), \
	1.initialization/0.env/get_env_path.c \
	1.initialization/0.env/get_env.c \
	1.initialization/0.env/utils.c \
	1.initialization/1.main/main.c \
	1.initialization/1.main/init_shell_env.c \
	1.initialization/1.main/shell_loop.c \
	1.initialization/2.tokenizer/token_generate.c \
	1.initialization/2.tokenizer/token_aux.c \
	1.initialization/2.tokenizer/even_more_token_aux.c \
	1.initialization/2.tokenizer/token_validate.c \
	1.initialization/3.expansor/expantion.c \
	1.initialization/3.expansor/expand_quotes.c \
	1.initialization/3.expansor/expand_var.c \
	1.initialization/3.expansor/utils.c \
	1.initialization/4.ast/ast.c \
	1.initialization/4.ast/ast_commands.c \
	1.initialization/4.ast/ast_tokens.c \
	1.initialization/5.parser/parser.c \
	1.initialization/5.parser/command_array.c \
	2.buildins/buildin_handler.c \
	2.buildins/cd.c \
	2.buildins/cd_utils.c \
	2.buildins/echo.c \
	2.buildins/env.c \
	2.buildins/export.c \
	2.buildins/export_utils.c \
	2.buildins/export_more_utils.c \
	2.buildins/pwd.c \
	2.buildins/unset.c \
	2.buildins/exit.c \
	3.execution/heredoc/heredoc.c \
	3.execution/heredoc/read_heredoc.c \
	3.execution/heredoc/utils.c \
	3.execution/redir/redirect.c \
	3.execution/redir/redirect_input.c \
	3.execution/redir/redirect_output.c \
	3.execution/redir/redir_setup.c \
	3.execution/redir/utils.c \
	3.execution/signal/signals.c \
	3.execution/fds_health.c \
	3.execution/child_process.c \
	3.execution/execution.c \
	3.execution/path_handler/path_command.c \
	3.execution/path_handler/path_utils.c \
	3.execution/path_handler/path_verification.c \
	3.execution/pipeline.c \
	3.execution/pipes.c \
	aux/error.c \
	aux/free.c \
	aux/terminal_health.c)

OBJS = $(SRCS:%.c=$(BUILD_DIR)%.o)
DEPS = $(OBJS:.o=.d)

# **************************************************************************** #
#                                   TOOLS                                       #
# **************************************************************************** #

MKDIR := mkdir -p
RM := rm -rf
SLEEP = sleep 0.1
CC = cc
AR = ar -rcs
SHELL := /bin/bash

# **************************************************************************** #
#                                   FLAGS                                       #
# **************************************************************************** #

CFLAGS = -Wall -Wextra -Werror
CPPFLAGS = $(addprefix -I,$(INCS_PATH)) -MMD -MP
LDLIBS = -ldl -pthread -lreadline
COMP_OBJ = $(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
COMP_EXEC = $(CC) $(OBJS) $(LIBS) $(LDLIBS) -o $(NAME)

# **************************************************************************** #
#                                  LIBRARIES                                    #
# **************************************************************************** #

LIBFT := $(LIBFT_DIR)libft.a
GARB := $(GARB_DIR)garbage_collector.a
LIBS := $(LIBFT) $(GARB)

# **************************************************************************** #
#                                   FUNCTIONS                                   #
# **************************************************************************** #

define create_dir
	$(MKDIR) $(dir $@)
endef

define comp_objs
	$(eval COUNT=$(shell expr $(COUNT) + 1))
	$(COMP_OBJ)
	$(SLEEP)
	printf "Compiling $(YELLOW)MINISHELL %d%%\r$(RESET) " $$(echo $$(($(COUNT) * 100 / $(words $(SRCS)))));
	@if [ $(COUNT) -eq $(words $(SRCS)) ]; then \
		printf "Compiled $(DARK_GREEN)MINISHELL  100%%$(RESET) "; \
		printf "\n"; \
	fi
endef

# **************************************************************************** #
#                                   RULES                                       #
# **************************************************************************** #

all: $(LIBFT) $(GARB) $(NAME)

$(BUILD_DIR)%.o: %.c
	$(call create_dir)
	$(call comp_objs)

$(NAME): $(OBJS)
	$(COMP_EXEC)
	printf "\n$(DARK_BLUE)$(NAME)$(RESET) is Ready \n"

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(GARB):
	$(MAKE) -C $(GARB_DIR)

clean:
	$(RM) $(BUILD_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(GARB_DIR) clean

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(GARB_DIR) fclean

re: fclean all

valgrind: re
	@valgrind --leak-check=full \
	--show-reachable=yes \
	--show-leak-kinds=all -s \
	--track-origins=yes \
	--suppressions=sup.supp \
	--log-file=valgrind.log \
	./$(NAME)
	@cat valgrind.log

help:
	@echo "Available targets:"
	@echo "  all       - Build the project"
	@echo "  clean     - Remove object files"
	@echo "  fclean    - Remove all files and libraries"
	@echo "  re        - Rebuild everything"
	@echo "  valgrind  - Run Valgrind on the executable"
	@echo "  help      - Show help"

-include $(DEPS)
