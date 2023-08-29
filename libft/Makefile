BLUE = \033[0;94m
GREEN = \e[1;92m
RED = \033[0;91m
RESET = \033[1;30m
WHITE = \033[1;97m
YELLOW = \033[1;33m

NAME = libft.a

CC = cc
CFLAGS = -Werror -Wextra -Wall

INC = -I ./inc/

SRC_PATH = src/
OBJ_PATH = obj/

SRC = $(addprefix $(SRC_PATH), \
	ft_atoi.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_dprintf.c \
	ft_freematrix.c \
	ft_freetensor.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_isspace.c \
	ft_itoa.c \
	ft_lstadd_back.c \
	ft_lstadd_front.c \
	ft_lstclear.c \
	ft_lstdelone.c \
	ft_lstiter.c \
	ft_lstlast.c \
	ft_lstmap.c \
	ft_lstnew.c \
	ft_lstsize.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_memset.c \
	ft_putchar_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_putstr_fd.c \
	ft_split.c \
	ft_strcat.c \
	ft_strchr.c \
	ft_strcmp.c \
	ft_strcpy.c \
	ft_strdup.c \
	ft_striteri.c \
	ft_strjoin.c \
	ft_strjoinfree.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strlen.c \
	ft_strmapi.c \
	ft_strncmp.c \
	ft_strncpy.c \
	ft_strnstr.c \
	ft_strpbrk.c \
	ft_strrchr.c \
	ft_strtrim.c \
	ft_substr.c \
	ft_tolower.c \
	ft_toupper.c \
	ft_triplejoin.c \
)


OBJ = $(SRC:$(SRC_PATH)%.c=$(OBJ_PATH)%.o)

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c | $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
	@printf "🔨	$(BLUE)Compiling $(WHITE)$(NAME)	$(BLUE)%-33s$(WHITE)\r" $(notdir $@)

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@echo "\n📦	$(WHITE)$(NAME)$(RESET)			$(YELLOW)compiled$(WHITE)"

clean:
	@rm -rf $(OBJ_PATH)

fclean: clean
	@rm -f $(NAME)
	@echo "🗑️	$(WHITE)$(NAME)$(RESET)			$(RED)removed$(WHITE)"

re: fclean all

NORM_CMD := $(shell which norminette 2>/dev/null || echo "/home/diogo/.local/bin/norminette")
norm:
	@OUTPUT=$$($(NORM_CMD) 2>&1); \
	ERROR_LINES=$$(echo "$$OUTPUT" | grep "Error"); \
	if [ -n "$$ERROR_LINES" ]; then \
		echo "❌	$(RESET)norminette $(WHITE)$(NAME)	$(RED)KO$(WHITE)"; \
		echo "$$ERROR_LINES"; \
	else \
		echo "✅	$(RESET)norminette $(WHITE)$(NAME)	$(GREEN)OK$(WHITE)"; \
	fi;

.PHONY: all re clean fclean norm