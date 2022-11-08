/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megrisse <megrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 01:37:01 by megrisse          #+#    #+#             */
/*   Updated: 2022/11/09 00:48:15 by megrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	norm_exec(t_cmnd *cmnd, t_global *glb, int old_fd, int red_back, int red_type)
{
	int	i;

	i = 0;
	if (cmnd->cmnd[0] != NULL)
	{	
		if (builtin_fct(cmnd, glb) != SUCCESS)
			i = -1;
	}
	if (red_type != 0)
		dup2(old_fd, red_back);
	free_tcmnd(cmnd);
	if (i == -1)
		return (FAILDE);
	return (SUCCESS);
}

int	exec_builting(t_list *cmnd_list, t_global *glb)
{
	t_cmnd	*cmnd;
	int		red_type;
	int		old_fd;
	int		red_back;
	int		i;

	red_type = 0;
	old_fd = -1;
	red_back = -1;
	i = 0;
	cmnd = initializ_cmnd(cmnd_list, glb->env);
	red_type = type_red(cmnd_list);
	if (red_type == R_OUT || red_type == DR_OUT)
	{
		old_fd = redirection_out(name_red(cmnd_list), red_type);
		red_back = STDOUT_FILENO;
	}
	else if (red_type == R_INP || red_type == DR_INP)
	{
		old_fd = redirection_inp(name_red(cmnd_list), red_type);
		red_back = STDIN_FILENO;
	}
	if (norm_exec(cmnd, glb, old_fd, red_back, red_type) != SUCCESS)
		return (FAILDE);
	return (SUCCESS);
}
