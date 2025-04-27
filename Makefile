#################################################
## COLORS
BLACK   = \033[0;30m
RED     = \033[0;31m
GREEN   = \033[0;32m
YELLOW  = \033[0;33m
BLUE    = \033[0;34m
MAGENTA = \033[0;35m
CYAN    = \033[0;36m
WHITE   = \033[0;37m
END     = \033[0m

################################################# 
## ARGUMENTS

NAME = minishell
INCLUDE = includes/minishell.h
CC = cc
FLAGS = -Wall -Wextra -Werror -O3 -g3
LIBFT_PATH = libft/
LIBFT = $(LIBFT_PATH)libft.a
BUILD   = objs/

#################################################
## SOURCES
SRC_FILES = exec/exec.c \
			exec/get_env.c \
			exec/get_inofile.c \
			exec/open_file.c \
			exec/get_path.c \
			exec/here_doc_utils.c \
			exec/here_doc.c \
			exec/pipe.c \
			exec/utils_exec.c \
			exec/utils_exec_2.c\
			exec/utils_exec_3.c \
			exec/utils_exec_4.c \
			exec/init_struct.c \
			builtin/builtin.c\
			builtin/cd_utils.c\
			builtin/cd.c\
			builtin/echo.c \
			builtin/echo_utils.c \
			builtin/env.c\
			builtin/exit.c\
			builtin/export.c\
			builtin/export_utils.c\
			builtin/export_utils_2.c \
			builtin/pwd.c \
			builtin/unset.c\
			main.c \
			parsing/cmds.c \
			parsing/expand.c \
			parsing/expand_utils.c \
			parsing/syntax.c \
			parsing/token.c \
			parsing/utils.c \
			exec/signal.c \

OBJECTS = $(addprefix $(BUILD), $(patsubst %.c, %.o, $(SRC_FILES)))

#################################################
## RULES

all: $(NAME)

$(NAME): $(OBJECTS)
	@make -C $(LIBFT_PATH)
	@$(CC) $(FLAGS) $(OBJECTS) $(LIBFT) -o $(NAME) -lreadline
	@echo "$(GREEN)Compilation done!$(END)"

$(BUILD)%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compilation of $< to $@..$(END)"
	@$(CC) $(FLAGS) -I$(LIBFT_PATH) -c $< -o $@

clean:
	@make clean -C $(LIBFT_PATH)
	@rm -rf $(BUILD)
	@echo "$(CYAN)Cleaning intermediate files.$(END)"

fclean: clean
	@make fclean -C $(LIBFT_PATH)
	@rm -f $(NAME)
	@echo "$(GREEN)All clean!$(END)"

re: fclean all

.PHONY: all clean fclean re