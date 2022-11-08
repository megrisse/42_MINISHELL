# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: megrisse <megrisse@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/09/21 18:05:22 by hmeur             #+#    #+#              #
#    Updated: 2022/11/09 00:29:54 by megrisse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#______________MAKEFILE_______________

NAME := Minishell

HEADER := mini.h

CC := gcc

CFLAGS += -Wall -Werror -Wextra

LDFLAGS += -lreadline

SRC :=	env.c \
		main.c \
		utils.c \
		pipe.c \
		t_list.c \
		signals.c \
		ft_itoa.c \
		commands.c \
		ft_split.c \
		init_cmnd.c \
		env_utils.c \
		exec_cmnds.c \
		redirection.c\
		exec_built.c \
		commands/cd.c \
		t_list_utils.c \
		t_list_utils1.c \
		t_list_utils2.c \
		commands/env_vars.c \
		commands/env_tools.c \

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
