/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megrisse <megrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 13:59:40 by megrisse          #+#    #+#             */
/*   Updated: 2022/11/09 00:48:42 by megrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"
#include <sys/types.h>
#include <sys/wait.h>

//protect all malloc in your minishell
int	check_red_name(char *str)
{
	char	c;
	int		i;

	i = 0;
	c = str[i];
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

int	check_syntax(t_list **list)
{
	t_list	*cmnd;
	int		prev;

	cmnd = *list;
	prev = -1;
	while (cmnd != NULL)
	{
		if (cmnd->type == PIPE && (prev == -1 || cmnd->next == NULL))
			return (ft_putstr_fd(2, "syntax error near unexpected token `|'\n"),
				free_list(list, *list), FAILDE);
		if (cmnd->type == PIPE)
			prev = -1;
		if (cmnd->type != WORD && cmnd->type != PIPE
			&& check_red_name(cmnd->str) == FAILDE)
			return (ft_putstr_fd(2,
					"syntax error near unexpected token `newline'\n"),
				free_list(list, *list), FAILDE);
		if (cmnd->type != PIPE && cmnd->next
			!= NULL && cmnd->next->type == PIPE)
			prev = 0;
		cmnd = cmnd->next;
	}
	return (SUCCESS);
}

void	norm_shell(t_global *global, char *line)
{
	int	n_cmnd;

	n_cmnd = nbr_mots(global->cmnd, '|');
	ft_pipes(global, n_cmnd);
	unlink(".heredoc");
	free(line);
	free_list(&global->cmnd_list, global->cmnd_list);
}

int	shell(t_global *global)
{
	char	*line;

	while (1337)
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
		norm_shell(global, line);
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
