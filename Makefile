# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hameur <hameur@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/21 18:05:22 by hmeur             #+#    #+#              #
#    Updated: 2022/11/01 17:56:00 by hameur           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#______________MAKEFILE_______________

NAME := Minishell

HEADER := mini.h

CC := gcc

CFLAGS += -Wall -Werror -Wextra

LDFLAGS += -lreadline

SRC :=	main.c \
		commands.c \
		env.c \
		env_utils.c \
		exec_cmnds.c \
		ft_split.c \
		ft_itoa.c \
		t_list.c \
		utils.c \
		redirection.c\
		init_cmnd.c \
		commands/cd.c \
		commands/env_vars.c \
		signals.c \


OBJS := $(SRC:.c=.o)

all :	$(NAME)
		@echo "Making Minishell"

$(NAME) :	$(OBJS)
	$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

%.o : %.c $(HEADER)
	$(CC) $(CFLAGS) -c $< -o $@ 

clean :
	@rm -rf $(OBJS)
	@echo "Removing objects files"

fclean : clean
	@rm -rf $(NAME)
	@echo "Removing Minishell"

re :	fclean all
