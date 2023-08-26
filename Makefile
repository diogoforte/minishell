# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bcastelo <bcastelo@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/10 05:13:54 by dinunes-          #+#    #+#              #
#    Updated: 2023/08/26 22:11:16 by bcastelo         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#Program name
NAME = minishell

# Compiler
CC = cc
CFLAGS = -Werror -Wextra -Wall #-fsanitize=address -g

# Libft
LIBFT_PATH	= libft/
LIBFT_NAME	= libft.a
LIBFT		= $(LIBFT_PATH)$(LIBFT_NAME)

# Includes
INC = -I ./inc/

# Sources and Objects paths
SRC_PATH = src/
OBJ_PATH = obj/

# Sources
SRC = $(addprefix $(SRC_PATH),	environment.c heredoc.c parsing2.c path.c signals.c variables.c\
								execute.c main.c parsing.c redirections.c pipe.c builtins.c builtins2.c  builtins3.c\
								exit.c structs.c pipe2.c pipe3.c parsing3.c input.c input2.c)

# Objects
OBJ = $(SRC:$(SRC_PATH)%.c=$(OBJ_PATH)%.o)

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c | $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

$(LIBFT):
	@make -sC $(LIBFT_PATH)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L$(LIBFT_PATH) -lft -lreadline
	@echo "\033[0;91m$(NAME) \033[0;0mready."

clean:
	@rm -rf $(OBJ_PATH)
	@make clean -sC $(LIBFT_PATH)

fclean: clean
	@rm -f $(NAME)
	@make fclean -sC $(LIBFT_PATH)
	@echo "\033[0;91m$(NAME) \033[0;0mfile removed."

re: fclean all

.PHONY: all re clean fclean
