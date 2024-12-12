#! ******************************************************************************#
#                                   NAME                                         #
#! ******************************************************************************#

NAME := minishell
.DEFAULT_GOAL := all
.PHONY: all clean fclean re rebonus help
.SILENT:

#! ******************************************************************************#
#                                   COLORS                                       #
#! ******************************************************************************#

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
YELLOW=\033[33m
RESET=\033[0m

#! ******************************************************************************#
#                                   PATHS                                        #
#! ******************************************************************************#

SRCS_PATH := src/
INCS_PATH := includes/ libs/libft/include/
BUILD_DIR := build/
LIBFT_DIR := libs/libft/
GARB_DIR := libs/garbage_collector/
TEST_DIR := tests/

#! ******************************************************************************#
#                                   FILES                                        #
#! ******************************************************************************#

SRCS := $(addprefix $(SRCS_PATH), \
	1.initialization/0.env/env.c \
	1.initialization/1.main/main.c \
	1.initialization/1.main/init_shell_env.c \
	1.initialization/1.main/shell_loop.c \
	1.initialization/2.tokenizer/token_generate.c \
	1.initialization/2.tokenizer/token_aux.c \
	1.initialization/2.tokenizer/token_validate.c \
	1.initialization/3.expansor/expansor.c \
	1.initialization/4.ast/ast.c \
	1.initialization/5.parser/parser.c \
	1.initialization/5.parser/command_array.c \
	2.buildins/buildin_handler.c \
	2.buildins/cd.c \
	2.buildins/echo.c \
	2.buildins/env.c \
	2.buildins/export.c \
	2.buildins/pwd.c \
	2.buildins/unset.c \
	2.buildins/exit.c \
	3.execution/heredoc/heredoc.c \
	3.execution/heredoc/read_heredoc.c \
	3.execution/heredoc/utils.c \
	3.execution/redir/redirect.c \
	3.execution/redir/redirect_input.c \
	3.execution/redir/redirect_output.c \
	3.execution/redir/setup_redirs.c \
	3.execution/redir/utils.c \
	3.execution/signal/signals.c \
	3.execution/fds_health.c \
	3.execution/child_process.c \
	3.execution/execution.c \
	3.execution/path_handler.c \
	3.execution/pipeline.c \
	3.execution/pipes.c \
	aux/debug.c \
	aux/error.c \
	aux/free.c \
	aux/terminal_health.c)

LIBFT := $(LIBFT_DIR)libft.a
GARB := $(GARB_DIR)garbage_collector.a
LIBS := $(LIBFT) $(GARB)
OBJS := $(SRCS:%.c=$(BUILD_DIR)%.o)
DEPS := $(OBJS:.o=.d)

#! ******************************************************************************#
#                                   COMMANDS                                     #
#! ******************************************************************************#

MKDIR := mkdir -p
RM := rm -rf
CC := $(shell which cc || echo gcc)
CFLAGS := -Wall -Wextra -Werror -g3
DFLAGS := -Wall -Wextra -Werror -g3 -fsanitize=address
CPPFLAGS := $(addprefix -I, $(INCS_PATH)) -MMD -MP
LDLIBS := -ldl -pthread -lreadline

#! ******************************************************************************#
#                                   FUNCTIONS                                    #
#! ******************************************************************************#

define create_dir
	$(MKDIR) $(dir $@)
endef

define comp_objs
	$(call create_dir)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	printf "$(YELLOW)Compiling: $(RESET)$<\n"
endef

define build_lib
	printf "$(YELLOW)Building library: $(RESET)$(1)\n"
	$(MAKE) -C $(1)
endef

define display_help
	printf "$(DARK_RED)Available targets:$(RESET)\n"
	printf "$(DARK_BLUE)all:$(RESET)        Build $(GREEN)$(NAME)$(RESET)\n"
	printf "$(DARK_BLUE)clean:$(RESET)      Remove object files\n"
	printf "$(DARK_BLUE)fclean:$(RESET)     Clean all files\n"
	printf "$(DARK_BLUE)re:$(RESET)         Rebuild everything\n"
endef

#! ******************************************************************************#
#                                   TARGETS                                      #
#! ******************************************************************************#

all: $(LIBFT) $(GARB) $(NAME)

$(BUILD_DIR)%.o: %.c
	$(call comp_objs)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBS) $(LDLIBS) -o $@
	printf "$(GREEN)$(NAME) is ready!$(RESET)\n"

$(LIBFT):
	$(call build_lib, $(LIBFT_DIR))

$(GARB):
	$(call build_lib, $(GARB_DIR))

clean:
	$(RM) $(BUILD_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(GARB_DIR) clean
	printf "$(RED)Cleaned object files.$(RESET)\n"

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(GARB_DIR) fclean
	printf "$(RED)Cleaned all files.$(RESET)\n"

re: fclean all

help:
	$(call display_help)

-include $(DEPS)
