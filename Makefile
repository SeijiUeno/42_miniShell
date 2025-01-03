#! ******************************************************************************#
#                                   NAME                                         #
#! ******************************************************************************#

NAME := minishell
.DEFAULT_GOAL := all
.PHONY: all clean fclean re

#! ******************************************************************************#
#                                   PATHS                                        #
#! ******************************************************************************#

SRCS_PATH := src/
INCS_PATH := includes/ libs/libft/include/
BUILD_DIR := build/
LIBFT_DIR := libs/libft/
GARB_DIR := libs/garbage_collector/

#! ******************************************************************************#
#                                   FILES                                        #
#! ******************************************************************************#

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

VALGRIND_LOG		= valgrind.log

OBJS := $(SRCS:%.c=$(BUILD_DIR)%.o)
DEPS := $(OBJS:.o=.d)

LIBFT := $(LIBFT_DIR)libft.a
GARB := $(GARB_DIR)garbage_collector.a
LIBS := $(LIBFT) $(GARB)

#! ******************************************************************************#
#                                   FLAGS                                        #
#! ******************************************************************************#

CC := cc
CFLAGS := -Wall -Wextra -Werror -g3
CPPFLAGS := $(addprefix -I, $(INCS_PATH)) -MMD -MP
LDLIBS := -ldl -pthread -lreadline
RM := rm -rf
MKDIR := mkdir -p

#! ******************************************************************************#
#                                   TARGETS                                      #
#! ******************************************************************************#

all: $(LIBFT) $(GARB) $(NAME)

$(BUILD_DIR)%.o: %.c
	$(MKDIR) $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
	printf "Compiling: $<\n"

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBS) $(LDLIBS) -o $@
	printf "$(NAME) is ready!\n"

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(GARB):
	$(MAKE) -C $(GARB_DIR)

clean:
	$(RM) $(BUILD_DIR)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(GARB_DIR) clean
	printf "Cleaned object files.\n"

fclean: clean
	$(RM) $(NAME)
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(GARB_DIR) fclean
	printf "Cleaned all files.\n"

re: fclean all

valgrind: re
	@valgrind --leak-check=full \
	--show-reachable=yes \
	--show-leak-kinds=all -s \
	--track-origins=yes \
	--suppressions=sup.supp \
	--log-file=$(VALGRIND_LOG) \
	./$(NAME)
	@cat $(VALGRIND_LOG)

-include $(DEPS)
