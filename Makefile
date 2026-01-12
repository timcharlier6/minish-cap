# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: csimonne <csimonne@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/11/06 20:48:27 by csimonne          #+#    #+#              #
#    Updated: 2026/01/12 19:08:51 by csimonne         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#REPERTOIRES-----------------------------------------------------------
HEADER = minishell.h
SRC = src/main.c src/parsing/tokenisation.c src/parsing/check_syntax.c \
		src/parsing/command_table.c src/parsing/expander.c \
		src/parsing/inits_and_signals.c src/error.c \
		src/parsing/sub_tokens_init.c src/parsing/sub_token_types.c\
		src/builtins/echo.c src/builtins/pwd.c \
		src/builtins/cd.c src/builtins/env.c src/exec.c \
		helpers/ft_strlen.c helpers/ft_strncpy.c \
		helpers/ft_space_related.c helpers/strdup_hub.c \
		helpers/char_search.c helpers/clean_up.c helpers/clean_lists.c \
		helpers/token_type_counter.c helpers/skip_word_or_adjacents.c \
		helpers/ft_calloc.c helpers/ft_strjoin_hub.c \
		helpers/ft_putstr_fd.c  helpers/ft_itoa.c \
		helpers/ft_putendl.c helpers/init_to_zero.c \
		helpers/strncmp_hub.c helpers/ft_strcmp.c

OBJ = $(SRC:.c=.o)
OBJDIR = obj

#VARIABLES-----------------------------------------------------------
NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -I. -g #-fsanitize=address

OBJ = $(addprefix $(OBJDIR)/, $(SRC:.c=.o))

#TARGETS(make)-----------------------------------------------------------

all : $(NAME)

$(NAME): $(OBJ) $(HEADER)
		$(CC) $(CFLAGS) -lreadline $(OBJ) -o $(NAME) 
#readline est une lib pas automatiquement linkee en C, donc on la linke ici.

$(OBJDIR)/%.o: %.c $(HEADER)
		@mkdir -p $(dir $@)
		$(CC) $(CFLAGS) -c $< -o $@

clean: 
		rm -rf $(OBJDIR)
fclean: clean
		rm -rf $(NAME)
re: fclean all

.PHONY: all re clean fclean
