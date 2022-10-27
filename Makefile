# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hmeur <hmeur@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/21 18:05:22 by hmeur             #+#    #+#              #
#    Updated: 2022/10/25 11:48:31 by hmeur            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#______________MAKEFILE_______________

NAME := Minishell

HEADER := mini.h

CC := gcc

CFLAGS := #-Wall -Werror -Wextra

READLINE_FLAG := -lreadline

SRC :=	readline.c \
		commands.c \
		env.c \
		env_utils.c \
		exec_cmnds.c \
		ft_split.c \
		t_list.c \
		utils.c \
		redirection.c\
		init_cmnd.c \
		commands/cd.c \
		commands/env_vars.c


OBJS := $(SRC:.c=.o)

all :	$(NAME)
		@echo "Making Minishell"

$(NAME) :	$(OBJS)
			@$(CC) $(CFLAGS) $(SRC) -o $(NAME) $(READLINE_FLAG)

%.o : %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

clean :
	@rm -rf $(OBJS)
	@echo "Removing objects files"

fclean : clean
	@rm -rf $(NAME)
	@echo "Removing Minishell"

re :	fclean all
