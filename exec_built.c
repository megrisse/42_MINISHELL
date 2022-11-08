/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_built.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megrisse <megrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 01:37:01 by megrisse          #+#    #+#             */
/*   Updated: 2022/11/08 03:27:49 by megrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

// int	builtin_fct(t_cmnd *cmnd, t_global *glb)
// {
// 	if (cmnd->cmnd[0] == NULL)
// 		return (FAILDE);
// 	if (ft_strncmp(cmnd->cmnd[0], (char *)"cd", 2) == SUCCESS)
// 		return (ft_cd(cmnd, &glb->env), SUCCESS);
// 	if (ft_strncmp(cmnd->cmnd[0], (char *)"pwd", 3) == SUCCESS)
// 		return (ft_pwd(cmnd, &glb->env), SUCCESS);
// 	if (ft_strncmp(cmnd->cmnd[0], (char *)"env", 3) == SUCCESS)
// 		return (ft_env(cmnd, &glb->env), SUCCESS);
// 	if (ft_strncmp(cmnd->cmnd[0], (char *)"echo", 4) == SUCCESS)
// 		return (ft_echo(cmnd, &glb->env), SUCCESS);
// 	if (ft_strncmp(cmnd->cmnd[0], (char *)"exit", 4) == SUCCESS)
// 		return (ft_exit(glb), SUCCESS);
// 	if (ft_strncmp(cmnd->cmnd[0], (char *)"unset", 5) == SUCCESS)
// 		return (ft_unset(cmnd, &glb->env), SUCCESS);
// 	if (ft_strncmp(cmnd->cmnd[0], (char *)"export", 6) == SUCCESS)
// 		return (ft_export(cmnd, &glb->env), SUCCESS);
// 	return (FAILDE);
// }

// int	red_inp(t_list *cmnd_list, t_global *glb, t_cmnd *cmnd, int red_type)
// {
// 	int	old_fd;
// 	int	red_back;
// 	int	i;

// 	old_fd = -1;
// 	red_back = -1;
// 	i = 0;
// 	if (red_type == R_INP || red_type == DR_INP)
// 	{
// 		old_fd = redirection_inp(name_red(cmnd_list), red_type);
// 		red_back = STDIN_FILENO;
// 	}
// 	if (cmnd->cmnd[0] != NULL)
// 	{	
// 		if (builtin_fct(cmnd, glb) != SUCCESS)
// 			i = -1;
// 	}
// 	if (red_type != 0)
// 		dup2(old_fd, red_back);
// 	free_tcmnd(cmnd);
// 	if (i == -1)
// 		return (FAILDE);
// 	return (SUCCESS);
// }

// int	exec_builting(t_list *cmnd_list, t_global *glb)
// {
// 	t_cmnd	*cmnd;
// 	int		red_type;
// 	int		old_fd;
// 	int		red_back;
// 	int		i;

// 	red_type = 0;
// 	cmnd = initializ_cmnd(cmnd_list, glb->env);
// 	red_type = type_red(cmnd_list);
// 	old_fd = -1;
// 	red_back = -1;
// 	i = 0;
// 	if (red_type == R_OUT || red_type == DR_OUT)
// 	{
// 		old_fd = redirection_out(name_red(cmnd_list), red_type);
// 		red_back = STDOUT_FILENO;
// 	}
// 	else if (red_type == R_INP || red_type == DR_INP)
// 	{
// 		old_fd = redirection_inp(name_red(cmnd_list), red_type);
// 		red_back = STDIN_FILENO;
// 	}
// 	if (cmnd->cmnd[0] != NULL)
// 	{	
// 		if (builtin_fct(cmnd, glb) != SUCCESS)
// 			i = -1;
// 	}
// 	if (red_type != 0)
// 		dup2(old_fd, red_back);
// 	free_tcmnd(cmnd);
// 	if (i == -1)
// 		return (FAILDE);
// 	// if (red_inp(cmnd_list, glb, cmnd, red_type) != SUCCESS)
// 	// 	return (FAILDE);
// 	return (SUCCESS);
// }
