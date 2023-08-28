BLUE = \033[0;94m
GREEN = \e[1;92m
RED = \033[0;91m
RESET = \033[1;30m
WHITE = \033[1;97m
YELLOW = \033[1;33m

NAME = minishell

CC = cc
CFLAGS = -Werror -Wextra -Wall -g #-fsanitize=address -g


LIBFT_PATH = libft/
LIBFT_NAME = libft.a
LIBFT = $(LIBFT_PATH)$(LIBFT_NAME)

INC = -I ./inc/

SRC_PATH = src/
OBJ_PATH = obj/

SRC = $(addprefix $(SRC_PATH), \
	environment.c \
	heredoc.c \
	parsing.c \
	parsing2.c \
	parsing3.c \
	path.c \
	signals.c \
	signals2.c \
	variables.c \
	execute.c \
	main.c \
	redirections.c \
	pipe.c \
	pipe2.c \
	pipe3.c \
	builtins.c \
	builtins2.c \
	builtins3.c \
	exit.c \
	structs.c \
	input.c \
	input2.c \
)


OBJ = $(SRC:$(SRC_PATH)%.c=$(OBJ_PATH)%.o)

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c | $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@
	@printf "🔨	Compiling $(WHITE)$(NAME)$(RESET):	$(BLUE)%-33s$(RESET)\r" $(notdir $@)

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

$(LIBFT):
	@make -sC $(LIBFT_PATH)

$(NAME): $(LIBFT) $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L$(LIBFT_PATH) -lft -lreadline
	@echo "\n📦	$(WHITE)$(NAME)$(RESET)		$(YELLOW)compiled$(WHITE)"

clean:
	@rm -rf $(OBJ_PATH)
	@make clean -sC $(LIBFT_PATH)

fclean: clean
	@rm -f $(NAME)
	@make fclean -sC $(LIBFT_PATH)
	@echo "🗑️	$(WHITE)$(NAME)$(RESET)		$(RED)removed$(RESET)"

re: fclean all

norm:
	@make norm -sC $(LIBFT_PATH)
	@OUTPUT=$$($(HOME)/.local/bin/norminette $(SRC) 2>&1); \
	ERROR_LINES=$$(echo "$$OUTPUT" | grep "Error"); \
	if [ -n "$$ERROR_LINES" ]; then \
		echo "$$ERROR_LINES"; \
		echo "❌	$(RESET)norminette $(WHITE)$(NAME)	$(RED)KO"; \
	else \
		echo "✅	$(RESET)norminette $(WHITE)$(NAME)	$(GREEN)OK"; \
	fi;

.PHONY: all re clean fclean norm
