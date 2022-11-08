/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megrisse <megrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 00:22:43 by megrisse          #+#    #+#             */
/*   Updated: 2022/11/09 00:54:24 by megrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	check_pipe(t_list *list, int t)
{
	t_list	*temp;

	temp = list;
	while (t != 0 && temp->next != NULL)
	{
		if (temp->next->type == PIPE)
			t--;
		temp = temp->next;
	}
	if (t == 0 && temp->type == PIPE && temp->next == NULL)
		return (FAILDE);
	return (SUCCESS);
}

int	ft_pipes(t_global *glb, int n_cmnd)
{
	t_list	*current;
	char	**cmnd;
	int		i;
	int		pid;

	current = NULL;
	i = 0;
	cmnd = ft_split(glb->cmnd, '|');
	pid = 1;
	glb->lastfd = -1;
	if (n_cmnd == 1)
	{
		current = init_list(glb, current, cmnd[0], check_quotes(cmnd[0]));
		if (exec_builting(current, glb) == SUCCESS)
			return (free_list(&current, current), ft_free(cmnd), SUCCESS);
		free_list(&current, current);
	}
	while (i < n_cmnd)
	{
		current = init_list(glb, current, cmnd[i], check_quotes(cmnd[i]));
		glb->p_in = glb->lastfd;
		if (cmnd[i + 1])
		{
			if (pipe(glb->fd) != SUCCESS)
				return (FAILDE);
			glb->p_out = glb->fd[1];
		}
		if (pid > 0)
			pid = fork();
		if (pid == 0)
		{
			handler_sig(glb, 1);
			dup2(glb->p_in, STDIN_FILENO);
			close(glb->p_in);
			dup2(glb->p_out, STDOUT_FILENO);
			close(glb->p_out);
			close(glb->fd[0]);
			exec_cmnd(current, glb);
		}
		close(glb->fd[1]);
		close(glb->p_in);
		i++;
		glb->lastfd = glb->fd[0];
		glb->fd[0] = -1;
		glb->fd[1] = -1;
		glb->p_out = -1;
		free_list(&current, current);
	}
	while (waitpid(-1, &glb->status, 0) > 0)
		;
	if (WIFEXITED(glb->status))
		glb->status = WEXITSTATUS(glb->status);
	else if (WIFSIGNALED(glb->status))
		glb->status = 128 + WTERMSIG(glb->status);
	close(glb->lastfd);
	return (ft_free(cmnd), SUCCESS);
}
