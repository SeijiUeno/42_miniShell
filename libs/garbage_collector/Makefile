NAME = garbage_collector.a
.DEFAULT_GOAL := all
.PHONY: all clean fclean re help
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
INCS_PATH = include/ ../libft/include/
BUILD_DIR := build/

# **************************************************************************** #
#                                   FILES                                       #
# **************************************************************************** #

SRCS =	$(addprefix $(SRCS_PATH),\
		garbage_collector.c \
		gc_tracker.c)
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
DFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address
LDLIBS = -ldl -lglfw -pthread
CPPFLAGS = $(addprefix -I,$(INCS_PATH)) -MMD -MP
COMP_OBJ = $(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
COMP_STATIC_LIB = $(AR) $(NAME) $(OBJS)

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
	printf "Compiling $(YELLOW)GARBAGE COLLECTOR %d%%\r$(RESET) " $$(echo $$(($(COUNT) * 100 / $(words $(SRCS)))))
	@if [ $(COUNT) -eq $(words $(SRCS)) ]; then \
		printf "Compiled $(DARK_GREEN)GARBAGE COLLECTOR  100%%$(RESET) "; \
		printf "\n"; \
	fi
endef

define comp_static_lib
	$(COMP_STATIC_LIB)
	printf "\n$(DARK_BLUE)$(NAME)$(RESET) is Ready \n"
	printf "\n"
endef

# **************************************************************************** #
#                                   RULES                                       #
# **************************************************************************** #

all: $(NAME)

# Build object files with progress bar
$(BUILD_DIR)%.o: %.c
	$(call create_dir)
	$(call comp_objs)

# Build static library
$(NAME): $(OBJS)
	$(call comp_static_lib)

# Clean object files
clean:
	$(RM) $(BUILD_DIR)

# Full clean (object files and library)
fclean: clean
	$(RM) $(NAME)

# Rebuild everything
re: fclean all

# Help Message
help:
	@echo "Available targets:"
	@echo "  all     - Build the library"
	@echo "  clean   - Remove object files"
	@echo "  fclean  - Remove object files and the library"
	@echo "  re      - Rebuild everything"
	@echo "  help    - Display this help message"

# Include dependencies
-include $(DEPS)
