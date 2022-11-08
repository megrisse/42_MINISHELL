/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_list_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megrisse <megrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 22:09:42 by megrisse          #+#    #+#             */
/*   Updated: 2022/11/08 22:22:02 by megrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	fct3(t_global *glb, char *str, char *ret, int **tab)
{
	char	c;

	c = str[(*tab[0])++];
	while (str[(*tab[0])] != 0 && str[*tab[0]] != c)
	{
		if (str[(*tab[0])] == '$' && c == DQUOTE)
			fct4(glb, str, ret, tab);
		else
			ret[(*tab[1])++] = str[(*tab[0])++];
	}
	(*tab[0])++;
}

char	*nume_var(char *str, int *id)
{
	char	*ret;
	int		i;
	int		j;

	j = (*id) + 1;
	i = 0;
	(*id)++;
	while (str[*id] != 0 && str[*id] != '$' && str[*id]
		!= ' ' && str[*id] != DQUOTE && str[*id] != SQUOTE)
	{
		i++;
		(*id)++;
	}
	ret = (char *)malloc(sizeof(char) * (i + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (str[j] != 0 && str[j] != '$' && str[j]
		!= ' ' && str[j] != DQUOTE && str[j] != SQUOTE)
		ret[i++] = str[j++];
	ret[i] = 0;
	return (ret);
}

int	check_list(t_list *list)
{
	t_list	*temp;

	temp = list;
	while (temp != NULL)
		temp = temp->next;
	return (SUCCESS);
}

int	check_quotes(char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0 && str[i] != DQUOTE && str[i] != SQUOTE)
		i++;
	if (str[i] == DQUOTE || str[i] == SQUOTE)
		return (1);
	return (0);
}
