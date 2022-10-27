/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeur <hmeur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 19:39:55 by hmeur             #+#    #+#             */
/*   Updated: 2022/10/24 17:35:21 by hmeur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int type_red(t_list *cmnd)
{
	t_list *temp = cmnd;
	while (temp != NULL && temp->type == WORD)
		temp = temp->next;
	if (temp == NULL)
		return (FAILDE);
	return (temp->type);
}


void	heredoc(char *file_name)
{
	unlink(".heredoc");
	int fd = open(".heredoc", O_CREAT | O_RDWR, 0664);
	char *line;
	while (1)
	{
		line = readline("heredoc> ");
		if (ft_strncmp(file_name, line, ft_strlen(file_name)) == 0)
			break ;
		ft_putstr_fd(fd, line);
		ft_putstr_fd(fd, "\n");
	}
	close(fd);
}

int redirection_inp(char *file_name, int red_type)
{
	int	fd;
	int	fd_cpy;

	if (red_type == DR_INP)
	{
		heredoc(file_name);
		fd = open(".heredoc", O_RDONLY);
	}
	if (red_type == R_INP)
		fd = open(file_name, O_RDONLY);
	fd_cpy = dup(STDIN_FILENO);
	if (fd_cpy < 0 || fd < 0 || dup2(fd, STDIN_FILENO) < 0)
		return (FAILDE);
	close(fd);
	return (fd_cpy);
}

int redirection_out(char *file_name, int red_type)
{
	int flags;
	int fd;
	int fd_cpy;

	if (red_type == R_OUT)
	{
		flags = O_CREAT | O_RDWR;
		unlink(file_name);
	}
	else if (red_type == DR_OUT)
		flags = O_CREAT | O_RDWR | O_APPEND;
	fd = open(file_name, flags, 0664);
	fd_cpy = dup(STDOUT_FILENO);
	if (fd_cpy < 0||fd < 0 || dup2(fd, STDOUT_FILENO) < 0)
		return (FAILDE);
	close(fd);
	return (fd_cpy);
}

char *name_red(t_list *cmnd_list)
{
	t_list *temp = cmnd_list;

	while (temp != NULL && temp->type == WORD)
		temp = temp->next;
	return (temp->next->str);
}
