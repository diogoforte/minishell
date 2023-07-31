# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/10 05:13:54 by dinunes-          #+#    #+#              #
#    Updated: 2023/07/31 09:06:31 by dinunes-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Program name
NAME = minishell

# Compiler
CC = cc
CFLAGS = -Werror -Wextra -Wall

# Libft
LIBFT_PATH	= libft/
LIBFT_NAME	= libft.a
LIBFT		= $(LIBFT_PATH)$(LIBFT_NAME)
LIBFT_SRC   = $(wildcard $(LIBFT_PATH)*.c)

# Includes
INC = -I ./inc/

# Sources and Objects paths
SRC_PATH = src/
OBJ_PATH = obj/

# Sources
SRC = $(addprefix $(SRC_PATH), main.c parsing.c builtins.c path.c utils.c signals.c)

# Objects
OBJ = $(SRC:$(SRC_PATH)%.c=$(OBJ_PATH)%.o)

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c | $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

$(LIBFT): $(LIBFT_SRC)
	@echo "Making \033[0;91mlibft\033[0;0m..."
	@make bonus -sC $(LIBFT_PATH) > /dev/null 2>&1
	@echo "\033[0;91mlibft \033[0;0mready."

$(NAME): $(OBJ) $(LIBFT)
	@echo "Compiling \033[0;91m$(NAME)\033[0;0m..."
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) $(LIBFT) -lreadline
	@echo "\033[0;91m$(NAME) \033[0;0mready."

clean:
	@echo "\033[0;0mRemoving \033[0;91m.o \033[0;0mobject files..."
	@rm -rf $(OBJ_PATH)
	@make clean -sC $(LIBFT_PATH) > /dev/null 2>&1
	@echo "\033[0;91m.o \033[0;0mobject files removed."

fclean: clean
	@echo "\033[0;0mRemoving \033[0;91m$(NAME)\033[0;0m..."
	@rm -f $(NAME)
	@rm -f $(LIBFT)
	@echo "\033[0;91m$(NAME) \033[0;0mfile removed."

re: fclean all

.PHONY: all re clean fclean