# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dinunes- <dinunes-@student.42lisboa.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/26 17:59:29 by dinunes-          #+#    #+#              #
#    Updated: 2023/08/02 04:19:33 by dinunes-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

# Compiler
CC = cc
CFLAGS = -Werror -Wextra -Wall

# Includes
INC = -I ./inc/

# Sources and Objects paths
SRC_PATH = src/
OBJ_PATH = obj/

# Sources
SRC = $(addprefix $(SRC_PATH), ft_atoi.c  ft_lstadd_back.c  ft_memchr.c  ft_split.c  ft_strmapi.c  \
                                ft_bzero.c  ft_lstadd_front.c  ft_memcmp.c  ft_strcat.c  ft_strncmp.c  \
                                ft_calloc.c  ft_lstclear.c  ft_memcpy.c  ft_strchr.c  ft_strncpy.c  \
                                ft_isalnum.c  ft_lstdelone.c  ft_memmove.c  ft_strdup.c  ft_strnstr.c  \
                                ft_isalpha.c  ft_lstiter.c  ft_memset.c  ft_striteri.c  ft_strrchr.c  \
                                ft_isascii.c  ft_lstlast.c  ft_putchar_fd.c  ft_strjoin.c  ft_strtrim.c  \
                                ft_isdigit.c  ft_lstmap.c  ft_putendl_fd.c  ft_strlcat.c  ft_substr.c  \
                                ft_isprint.c  ft_lstnew.c  ft_putnbr_fd.c  ft_strlcpy.c  ft_tolower.c  \
                                ft_itoa.c  ft_lstsize.c  ft_putstr_fd.c  ft_strlen.c  ft_toupper.c )

# Objects
OBJ = $(SRC:$(SRC_PATH)%.c=$(OBJ_PATH)%.o)

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c | $(OBJ_PATH)
	@$(CC) $(CFLAGS) $(INC) -c $< -o $@

$(OBJ_PATH):
	@mkdir -p $(OBJ_PATH)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@echo "\033[0;91m$(NAME) \033[0;0mready."

clean:
	@rm -rf $(OBJ_PATH)

fclean: clean
	@rm -f $(NAME)
	@echo "\033[0;91m$(NAME) \033[0;0mfile removed."

re: fclean all

.PHONY: all re clean fclean
