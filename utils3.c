/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megrisse <megrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 22:52:39 by hameur            #+#    #+#             */
/*   Updated: 2022/11/11 19:34:18 by megrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	exec_child(t_global *glb, t_list *current)
{
	handler_sig(glb, 1);
	dup2(glb->p_in, STDIN_FILENO);
	close(glb->p_in);
	dup2(glb->p_out, STDOUT_FILENO);
	close(glb->p_out);
	close(glb->fd[0]);
	exec_cmnd(current, glb);
}

void	init_fds(t_global *glb, int *i)
{
	close(glb->fd[1]);
	close(glb->p_in);
	(*i)++;
	glb->lastfd = glb->fd[0];
	glb->fd[0] = -1;
	glb->fd[1] = -1;
	glb->p_out = -1;
}

int	check_red_name(char *str)
{
	int		i;
	char	c;

	i = 0;
	c = str[i];
	while (str[i] != 0 && str[i] == c && i < 2)
		i++;
	if (str[i] == 0 || str[i] == '>' || str[i] == '<' || str[i] == '|')
		return (FAILDE);
	return (SUCCESS);
}

int	check_pipe(char *str, int key)
{
	int	i;

	i = 0;
	while (str[i] != 0 && str[i] != '|')
		i++;
	if (key == 0 && i > 0 && str[i - 1] != '|')
		return (SUCCESS);
	else if (key == 1 && str[i] != 0 && str[i + 1] != 0 && str[i + 1] != '|')
		return (SUCCESS);
	return (FAILDE);
}

int	check_syntax(t_list **list)
{
	t_list	*cmnd;
	int		prev;

	prev = -1;
	cmnd = *list;
	if (cmnd == NULL)
		return (FAILDE);
	while (cmnd != NULL)
	{
		if (check_syntax_utils(list, cmnd, &prev) != SUCCESS)
			return (FAILDE);
		cmnd = cmnd->next;
	}
	return (SUCCESS);
}
