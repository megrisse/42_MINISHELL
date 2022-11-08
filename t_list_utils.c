/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_list_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megrisse <megrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:32:03 by megrisse          #+#    #+#             */
/*   Updated: 2022/11/08 23:52:44 by megrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_putstr_fd(int fd, char *str)
{
	int	i;

	i = -1;
	while (str[++i] != 0)
		write(fd, &str[i], 1);
	return (i);
}

int	is_file(char *str)
{
	if (ft_strncmp(str, "./", 1) == SUCCESS)
		return (FAILDE);
	return (SUCCESS);
}

int	is_word(char *str)
{
	int	i;

	i = -1;
	while (str[++i] != 0)
	{
		if (str[i] == '|' || str[i] == '>' || str[i] == '<')
			return (FAILDE);
	}
	return (SUCCESS);
}

void	free_list(t_list **root, t_list *node)
{
	if (node == NULL)
		return ;
	free_list(root, node->next);
	free(node->str);
	free(node);
}

int	check_type(char *str, int key)
{
	if (key == 1)
		return (WORD);
	else if (key == 0 && is_word(str) == SUCCESS)
		return (WORD);
	else if (str[0] == '|' && str[1] == 0)
		return (PIPE);
	else if (str[0] == '>' && str[1] != '>')
		return (R_OUT);
	else if (str[0] == '<' && str [1] != '<')
		return (R_INP);
	else if (str[0] == '>' && str[1] == '>')
		return (DR_OUT);
	else if (str[0] == '<' && str[1] == '<')
		return (DR_INP);
	return (FAILDE);
}
