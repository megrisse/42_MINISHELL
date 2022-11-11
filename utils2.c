/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 19:08:34 by hameur            #+#    #+#             */
/*   Updated: 2022/11/10 22:55:44 by hameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	is_file(char *str)
{
	if (ft_strncmp(str, "./", 1) == SUCCESS)
		return (FAILDE);
	return (SUCCESS);
}

void	print_error(char *cmnd, int i)
{
	ft_putstr_fd(2, cmnd);
	if (i == 0)
		ft_putstr_fd(2, (char *)": No such file or directory\n");
	else if (i == 1)
		ft_putstr_fd(2, (char *)": command not found\n");
}

void	init_glb(t_global *glb, int *n_cmnd)
{
	(*n_cmnd) = 0;
	glb->p_in = -1;
	glb->p_out = -1;
}

int	init_and_check(t_global *glb, char *line)
{
	glb->cmnd = line;
	glb->cmnd_list = init_list(glb, glb->cmnd_list, line, 0);
	if (check_syntax(&glb->cmnd_list) != SUCCESS)
		return (FAILDE);
	return (SUCCESS);
}

int	check_syntax_utils(t_list **list, t_list *cmnd, int *prev)
{
	if (cmnd->type == PIPE
		&& (((*prev) == -1 && check_pipe(cmnd->str, 0) == FAILDE)
			|| (cmnd->next == NULL && check_pipe(cmnd->str, 1) == FAILDE)))
		return (free_list(list, *list), ft_putstr_fd(2,
				"syntax error near unexpected token `|'\n"), FAILDE);
	if (cmnd->type == PIPE)
		(*prev) = -1;
	if (cmnd->type != WORD && cmnd->type != PIPE
		&& check_red_name(cmnd->str) == FAILDE && cmnd->next == NULL)
		return (free_list(list, *list), ft_putstr_fd(2,
				"syntax error near unexpected token `newline'\n"), FAILDE);
	if (cmnd->type != PIPE && cmnd->next != NULL && cmnd->next->type == PIPE)
		(*prev) = 0;
	return (SUCCESS);
}
