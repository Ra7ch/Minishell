# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: raitmous <raitmous@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/04 18:33:38 by mben-zeh          #+#    #+#              #
#    Updated: 2023/06/25 02:22:47 by raitmous         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

CFLAGS = -Wall -Werror -Wextra 

SRC = builtins/builtins_1.c builtins/builtins_2.c builtins/builtins_3.c builtins/builtins_4.c builtins/builtins_5.c execution/execution_1.c execution/execution_2.c execution/execution_3.c execution/execution_4.c execution/execution_5.c execution/execution_6.c execution/execution_7.c parsing/parsing_1.c parsing/parsing_2.c parsing/parsing_3.c parsing/parsing_4.c parsing/parsing_error.c parsing/parsing_expand_1.c parsing/parsing_expand_2.c parsing/parsing_wildcard_1.c parsing/parsing_wildcard_2.c utils/utils_1.c utils/utils_2.c utils/utils_3.c utils/utils_4.c utils/utils_5.c utils/utils_6.c utils/utils_7.c utils/utils_free_1.c utils/utils_free_2.c utils/utils_split.c main.c

INCLUDE = -L/${HOME}/Desktop/readline-8.2 -I/${HOME}/Desktop/readline-8.2 -lcurses

OBJ = ${SRC:.c=.o}

all : ${NAME}

${NAME} : ${OBJ}
	@$(CC)  $(OBJ) $(INCLUDE) -o ${NAME} -lreadline 

clean :
	rm -f ${OBJ}

bonus : all

fclean : clean
	rm -f ${NAME}

re : fclean all

.PHONY: all clean fclean re