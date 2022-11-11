/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 16:12:09 by hameur            #+#    #+#             */
/*   Updated: 2022/11/10 19:10:22 by hameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

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

int	is_special(char c, int key)
{
	if (key == 1)
		return (SUCCESS);
	if (c == '|')
		return (PIPE);
	else if (c == '>')
		return (R_OUT);
	else if (c == '<')
		return (R_INP);
	return (FAILDE);
}

int	end_red(char *str, char c)
{
	if (c == '|')
		return (0);
	if (str[0] == c && str[1] == c)
		return (1);
	return (0);
}

int	check_type(char *str, int key)
{
	int	i;

	i = 0;
	if (key == 1)
		return (WORD);
	else if (key == 0 && is_word(str) == SUCCESS)
		return (WORD);
	else if (str[0] == '>' && str[1] != '>')
		return (R_OUT);
	else if (str[0] == '<' && str [1] != '<')
		return (R_INP);
	else if (str[0] == '>' && str[1] == '>')
		return (DR_OUT);
	else if (str[0] == '<' && str[1] == '<')
		return (DR_INP);
	else if (str[0] == '|')
		return (PIPE);
	else if (is_word(str) == FAILDE)
	{
		while (str[i] != 0 && str[i] != '|')
			i++;
		if (str[i] == '|')
			return (PIPE);
	}
	return (FAILDE);
}

int	next_q(char *s, int i, char c)
{
	i++;
	while (s[i] != 0 && s[i] != c)
		i++;
	if (s[i] == 0)
		return (i);
	return (i + 1);
}
