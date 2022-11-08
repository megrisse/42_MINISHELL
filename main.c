/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megrisse <megrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 13:59:40 by megrisse          #+#    #+#             */
/*   Updated: 2022/11/08 20:13:46 by megrisse         ###   ########.fr       */
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

int	ft_pipes(t_global *glb, int n_cmnd)
{
	t_list	*current = NULL;
	char	**cmnd;
	int		fd[2];
	int		i;
	int		pid = 1;
	int		lastfd = -1;
	
	i = 0;
	cmnd = ft_split(glb->cmnd, '|');
	int j = 0;
	while (cmnd[j++] != NULL);
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
		glb->p_in = lastfd;
		if (cmnd[i + 1])
		{
			if (pipe(fd) != SUCCESS)
				return (FAILDE);
			glb->p_out = fd[1];
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
	}
	while (waitpid(-1, &glb->status, 0) > 0);
	if (WIFEXITED(glb->status))
		glb->status = WEXITSTATUS(glb->status);
	else if (WIFSIGNALED(glb->status))	
		glb->status = 128 + WTERMSIG(glb->status);
	close(lastfd);
	return (ft_free(cmnd), SUCCESS);
}

int check_red_name(char *str)
{
	int i = 0;
	char c = str[i];
	while (str[i] != 0 && str[i] == c)
		i++;
	if (c == '>')
		c = '<';
	else if (c == '<')
		c = '>';
	if (str[i] == 0 || str[i] == c)
		return (FAILDE);
	return (SUCCESS);
}

int check_syntax(t_list **list)
{
	int prev = -1;
	t_list *cmnd = *list;
	while (cmnd != NULL)
	{
		if (cmnd->type == PIPE && (prev == -1 || cmnd->next == NULL))
			return (ft_putstr_fd(2, "syntax error near unexpected token `|'\n"), free_list(list, *list), FAILDE);
		if (cmnd->type == PIPE)
			prev = -1;
		if (cmnd->type != WORD && cmnd->type != PIPE && check_red_name(cmnd->str) == FAILDE)
			return (ft_putstr_fd(2, "syntax error near unexpected token `newline'\n"), free_list(list, *list), FAILDE);
		if (cmnd->type != PIPE && cmnd->next != NULL && cmnd->next->type == PIPE)
			prev = 0;
		cmnd = cmnd->next;
	}
	return (SUCCESS);
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
		global->cmnd_list = init_list(global, global->cmnd_list, line, 0);
		if (check_syntax(&global->cmnd_list) != SUCCESS)
			continue ;
		if (global->cmnd_list == NULL)
			continue ;
		n_cmnd = nbr_mots(global->cmnd, '|');
		ft_pipes(global, n_cmnd);
		unlink(".heredoc");
		free(line);
		free_list(&global->cmnd_list, global->cmnd_list);
	}
	return (SUCCESS);
}

int main(int ac, char **av, char **env)
{
	t_global *global;
	(void)ac;
	(void)av;
	
	global = (t_global *)malloc(sizeof(t_global));
	global->env = init_envi(env);
	handler_sig(global, 0);
	shell(global);
	return (SUCCESS);
}
