/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megrisse <megrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 13:59:40 by megrisse          #+#    #+#             */
/*   Updated: 2022/11/05 20:03:45 by megrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"
#include <sys/types.h>
#include <sys/wait.h>

//protect all malloc in your minishell

int	check_pipe(t_list *list, int t)
{
	t_list *temp;

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

void init_parties(t_global *glb, t_list **left, t_list **right, int pipe_num)
{
	int total_pipes = nbr_mots(glb->cmnd, '|');
	if (glb->cmnd_list->type == PIPE)
		return ;
	if (check_pipe(glb->cmnd_list, total_pipes) == FAILDE)
		return ;
	char **str = ft_split(glb->cmnd, '|');
	if (str == NULL)
		return ;
	*left = init_list(glb, *left, str[total_pipes - pipe_num]);
	if (str[total_pipes - pipe_num + 1] != NULL)
		*right = init_list(glb, *right, str[total_pipes - pipe_num + 1]);
	else
		right = NULL;
	ft_free(str);
}




int close_fds(t_list *right, int *fd, int *old_fd, int key)
{
	if (key == 1)
	{
		if (old_fd != NULL)
		{
			close(old_fd[0]);
			close(old_fd[1]);
		}
	}
	else
	{
		if (old_fd != NULL)
		{
			dup2(old_fd[0], STDIN_FILENO);
			close(old_fd[0]);
			close(old_fd[1]);
		}
		if (right != NULL)
		{
			dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
		}
	}
	return (SUCCESS);
}

int exec_builting(t_list *cmnd_list, t_global *glb)
{
	t_cmnd	*cmnd;
	int		red_type = 0;
	int		old_fd = -1;
	int		red_back = -1;
	int		i = 0;

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


// int ft_pipes(t_global *global, int pipe_num, int *old_fd, int key)
// {
// 	t_list *left_cmnd = NULL;
// 	t_list *right_cmnd = NULL;


// 	init_parties(global, &left_cmnd, &right_cmnd, pipe_num);
// 	if (left_cmnd == NULL)
// 		return (write(2, "Error Pipe\n", 11), FAILDE);
// 	if (key == 0 && right_cmnd == NULL)
// 		global->status = exec_builting(global->cmnd_list, global);
// 	if (key == 0 && right_cmnd == NULL && global->status == SUCCESS)
// 		return (free_list(&left_cmnd, left_cmnd), unlink(".heredoc"), SUCCESS);
// 	int	fd[2];
// 	if (pipe(fd) < 0)
// 		return (FAILDE);
// 	int	pid = fork();
// 	if (pid < 0)
// 		return (FAILDE);
// 	if (pid == 0)
// 	{
// 		close(fd[0]);
// 		close_fds(right_cmnd, fd, old_fd, 0);
// 		if (exec_cmnd(left_cmnd, global) != SUCCESS)
// 			return (FAILDE);
// 		return (free_list(&left_cmnd, left_cmnd), SUCCESS);
// 	}
// 	if (pid > 0)
// 	{
// 		close_fds(NULL, fd, old_fd, 1);
// 		wait(&global->status);
// 		if (right_cmnd != NULL)
// 			ft_pipes(global, --pipe_num, fd, 1);
// 	}
// 	free_list(&left_cmnd, left_cmnd);
// 	if (right_cmnd != NULL)
// 		free_list(&right_cmnd, right_cmnd);
// 	return (0);
// }


// int	execute_cmnd(t_global *glb, t_list *current, int i, int *fd)
// {
// 	int	t_pipe;

// 	t_pipe = nbr_mots(glb->cmnd, '|');
// 	// if (t_pipe == 1)
// 	// 	return (exec_cmnd(current, glb), exit(0), SUCCESS);
// 	// if (pipe(fd) == FAILDE)
// 	// 	return (FAILDE);
// 	if (i == 0)
// 	{
// 		dup2(fd[1], STDOUT_FILENO);
// 		close(fd[0]);
// 		close(STDOUT_FILENO);
// 	}
// 	if (i == t_pipe - 1)
// 	{
// 		dup2(fd[0], STDIN_FILENO);
// 		close(fd[1]);
// 		close(STDIN_FILENO);
// 	}
// 	else
// 	{
// 		dup2(fd[0], STDIN_FILENO);
// 		dup2(fd[1], STDOUT_FILENO);
// 		close(STDOUT_FILENO);
// 		close(STDIN_FILENO);
// 	}
// 	if (exec_cmnd(current, glb) != SUCCESS)
// 			exit(FAILDE);
// 	exit(SUCCESS);
// }

// int	exec_other(t_global *glb, t_list *current)
// {
// 	int pid;
// 	int ret = 0;

// 	pid = fork();
// 	if (pid == 0)
// 		ret = exec_cmnd(current, glb);
// 	else
// 		wait(&glb->status);
// 	return (ret);
// }

// int ftt_pipes(t_global *glb)
// {
// 	t_list	*current = NULL;
// 	char	**cmnd;
// 	int		t_pipe;
// 	int		fd[2];
// 	int		i = 0;
// 	int		pid = 1;
	
// 	// if (pipe(glb->fd) == FAILDE)
// 	// 	return (FAILDE);
// 	cmnd = ft_split(glb->cmnd, '|');
// 	t_pipe = nbr_mots(glb->cmnd, '|');
// 	glb->p_in = fd[0];
// 	glb->p_out = fd[1];
// 	if (t_pipe == 1)
// 	{
// 		current = init_list(glb, current, cmnd[0]);
// 		if (exec_builting(current, glb) == SUCCESS)
// 			return (free_list(&current, current), SUCCESS);
// 		free_list(&current, current);
// 	}
// 	while (i != t_pipe)
// 	{
// 		current = init_list(glb, current, cmnd[i++]);
// 		t_list *next = init_list(glb, current, cmnd[i]);
// 		if (next)
// 		{
// 			if (pipe(fd) != SUCCESS)
// 				return(FAILDE);
// 		}
// 		if (pid > 0)
// 			pid = fork();
// 		if (pid == 0)
// 		{
// 			close(fd[0]);
// 			glb->p_out = fd[1];
// 			execute_cmnd(glb, current, i - 1, fd);
// 			exit(0);
// 		}
// 		// if (pid != 0 && i == t_pipe)
// 		// {
// 		// 	// printf("before i == %d   t_pipe == %d\n", i, t_pipe);
			
// 		// 	// printf("after i == %d   t_pipe == %d\n", i, t_pipe);
// 		// 	close(fd[0]);
// 		// 	close(fd[1]);
// 		// }
// 		close (fd[1]);
// 		glb->p_in = fd[0];
// 		fd[0] = -1;
// 		fd[1] = -1;
// 		free_list(&current, current);
// 	}
// 	while (waitpid(pid, &glb->status, -1) > 0);
// 	close(glb->p_in);
// 	close(glb->p_out);
// 	// printf("i'm here from %d prosses\n", pid);
// 	return (SUCCESS);
// }



int	ft_pipes(t_global *glb)
{
	t_list	*current = NULL;
	char	**cmnd;
	int		fd[2];
	int		i;
	int		pid = 1;
	int		lastfd = -1;
	
	i = 0;
	cmnd = ft_split(glb->cmnd, '|');
	// if (nbr_mots(glb->cmnd, '|') == 1)
	// {
	// 	current = init_list(glb, current, cmnd[0]);
	// 	if (exec_builting(current, glb) == SUCCESS)
	// 		return (free_list(&current, current), SUCCESS);
	// 	free_list(&current, current);
	// }
	while (i < nbr_mots(glb->cmnd, '|'))
	{
		current = init_list(glb, current, cmnd[i]);
		glb->p_in = lastfd;
		if (cmnd[i + 1])
		{
			if (pipe(fd) != SUCCESS)
				return (FAILDE);
			// glb->p_in = fd[0];
			glb->p_out = fd[1];
		}
		if (pid > 0)
			pid = fork();
		if (pid == 0)
		{
			dup2(glb->p_in, STDIN_FILENO);
			close(glb->p_in);
			dup2(glb->p_out, STDOUT_FILENO);
			close(glb->p_out);
			close(fd[0]);
			exec_cmnd(current, glb);
		}
		close(fd[1]);
		close(glb->p_in);
		i++;
		lastfd = fd[0];
		fd[0] = -1;
		fd[1] = -1;
		glb->p_out = -1;
		free_list(&current, current);
		// free_list(&current, current);
	}
	while (waitpid(-1, &glb->status, 0) > 0);
	close(lastfd);
	return (ft_free(cmnd), SUCCESS);
}

int shell(t_global *global)
{
	char *line;
	int	n_cmnd;
	while(1337)
	{
		global->p_in = -1;
		global->p_out = -1;
		line = readline("Minishel => ");
		if (line == NULL)
			ft_exit(global);
		if (ft_strlen(line) != 0)
			add_history(line);
		else
			continue ;
		global->cmnd = line;
		global->cmnd_list = init_list(global, global->cmnd_list, line);
		if (global->cmnd_list == NULL)
			continue ;
		n_cmnd = nbr_mots(global->cmnd, '|');
		global->status = ft_pipes(global);
		free(line);
		free_list(&global->cmnd_list, global->cmnd_list);
	}
	return (SUCCESS);
}

int main(int ac, char **av, char **env)
{
	t_global *global;
	global = (t_global *)malloc(sizeof(t_global));
	global->env = init_envi(env);

	//env valide
	(void)ac;(void)av;
	handler_sig(global);
	shell(global);
	return (SUCCESS);
}
