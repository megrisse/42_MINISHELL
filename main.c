/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 13:59:40 by megrisse          #+#    #+#             */
/*   Updated: 2022/11/11 16:31:00 by hameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	pipe_utils(t_global *glb, t_list *current, char **cmnd, int n_cmnd)
{
	int	i;

	i = 0;
	while (i < n_cmnd)
	{
		current = init_list(glb, current, cmnd[i], check_quotes(cmnd[i]));
		glb->p_in = glb->lastfd;
		if (cmnd[i + 1])
		{
			pipe(glb->fd);
			glb->p_out = glb->fd[1];
		}
		if (glb->pid > 0)
			glb->pid = fork();
		if (glb->pid < 0)
			return (ft_putstr_fd(2,
					"fork: Resource temporarily unavailable\n"), 1);
		if (glb->pid == 0)
			exec_child(glb, current);
		init_fds(glb, &i);
		free_list(&current, current);
	}
	return (SUCCESS);
}

void	exit_status(t_global *glb)
{
	if (WIFEXITED(glb->status))
		glb->status = WEXITSTATUS(glb->status);
	else if (WIFSIGNALED(glb->status))
		glb->status = 128 + WTERMSIG(glb->status);
}

int	ft_pipes(t_global *glb, int n_cmnd)
{
	t_list	*current;
	char	**cmnd;

	current = NULL;
	glb->lastfd = -1;
	glb->pid = 1;
	cmnd = ft_split(glb->cmnd, '|');
	if (n_cmnd == 1 && exec_onecmnd(glb, current, cmnd) == SUCCESS)
		return (ft_free(cmnd), SUCCESS);
	if (pipe_utils(glb, current, cmnd, n_cmnd) == FAILDE)
		return (ft_free(cmnd), FAILDE);
	while (waitpid(-1, &glb->status, 0) > 0)
		;
	exit_status(glb);
	close(glb->lastfd);
	return (ft_free(cmnd), SUCCESS);
}

int	shell(t_global *global)
{
	char	*line;
	int		n_cmnd;

	line = NULL;
	while (1337)
	{
		if (line != NULL)
			free(line);
		init_glb(global, &n_cmnd);
		line = readline("Minishel => ");
		if (line == NULL)
			ft_exit(global);
		if (ft_strlen(line) != 0)
			add_history(line);
		else
			continue ;
		if (init_and_check(global, line) == FAILDE)
			continue ;
		n_cmnd = nbr_mots(global->cmnd, '|', n_cmnd);
		ft_pipes(global, n_cmnd);
		unlink(".heredoc");
		free_list(&global->cmnd_list, global->cmnd_list);
	}
	return (SUCCESS);
}

int	main(int ac, char **av, char **env)
{
	t_global	*global;

	(void)ac;
	(void)av;
	global = (t_global *)malloc(sizeof(t_global));
	global->env = init_envi(env);
	handler_sig(global, 0);
	shell(global);
	return (SUCCESS);
}
