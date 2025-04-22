#################################################
## COLORS
BLACK = \033[0;30m
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
END = \033[0m

#################################################
## ARGUMENTS

NAME				= libft.a
CFLAGS				= -Wall -Werror -Wextra
CC					= cc
AR					= ar -rcs
BUILD				= objs/
INCLUDE 			= includes/


#################################################
## SOURCES

SRC_FILES			= ft_atoi \
                    ft_bzero \
                    ft_calloc \
                    ft_isalnum \
                    ft_isalpha \
                    ft_isascii \
                    ft_isdigit \
                    ft_isprint \
                    ft_memchr \
                    ft_memcmp \
                    ft_memcpy \
                    ft_memmove \
                    ft_memset \
                    ft_strchr \
                    ft_strdup \
                    ft_strndup \
                    ft_strlcat \
                    ft_strlcpy \
                    ft_strlen \
                    ft_strncmp \
                    ft_strnstr \
                    ft_strrchr \
                    ft_tolower \
                    ft_toupper \
                    ft_substr \
                    ft_putchar_fd \
                    ft_putstr_fd \
                    ft_putendl_fd \
                    ft_putnbr_fd \
                    ft_strjoin \
                    ft_strtrim \
                    ft_itoa \
                    ft_strmapi \
                    ft_striteri \
                    ft_split \
                    ft_printf \
                    ft_print_char \
                    ft_print_hexa \
                    ft_print_nbr \
                    ft_print_ptr \
                    ft_print_str \
                    ft_print_unsigned \
                    ft_putchar \
                    ft_putstr \
                    get_next_line \
                    get_next_line_utils \

OBJ_FILES			= $(addprefix $(BUILD), $(addsuffix .o, ${SRC_FILES}))

SRC_BONUS			= ft_lstnew \
                    ft_lstadd_front \
                    ft_lstsize \
                    ft_lstlast \
                    ft_lstadd_back \
                    ft_lstdelone \
                    ft_lstclear \
                    ft_lstiter \
                    ft_lstmap

OBJ_BONUS			= $(addprefix $(BUILD), $(addsuffix .o, $(SRC_BONUS)))

#################################################
## RULES

all : ${NAME}

${NAME} : ${OBJ_FILES}
	@${AR} ${NAME} ${OBJ_FILES}
	@echo "$(GREEN)Libft : Compilation done! 👍$(END)"

$(BUILD)%.o: srcs/%.c
	@mkdir -p ${BUILD}
	@${CC} ${CFLAGS} -I$(INCLUDE) -c $< -o $@

$(BUILD)%.o: bonus/%.c
	@mkdir -p ${BUILD}
	@${CC} ${CFLAGS} -I$(INCLUDE) -c $< -o $@

bonus : ${OBJ_BONUS}
	@${AR} ${NAME} ${OBJ_BONUS}
	@echo "$(GREEN)Libft : Compilation bonus done! 👍$(END)"

clean :
	@rm -rf ${BUILD}
	@echo "$(CYAN)Libft : Cleaning intermediate files.$(END)"

fclean : clean
	@rm -f ${NAME}
	@echo "$(GREEN)Libft : All clean!$(END)"

re : fclean all

.PHONY : all clean fclean re bonus