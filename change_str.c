/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_str.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 15:34:52 by hameur            #+#    #+#             */
/*   Updated: 2022/11/10 16:13:15 by hameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*nume_var(char *str, int *id)
{
	char	*ret;
	int		i;
	int		j;

	j = (*id) + 1;
	i = 0;
	(*id)++;
	while (str[*id] != 0 && str[*id] != '$'
		&& str[*id] != ' ' && str[*id] != DQUOTE && str[*id] != SQUOTE)
	{
		i++;
		(*id)++;
	}
	ret = (char *)malloc(sizeof(char) * (i + 1));
	if (!ret)
		return (NULL);
	i = 0;
	while (str[j] != 0 && str[j] != '$'
		&& str[j] != ' ' && str[j] != DQUOTE && str[j] != SQUOTE)
		ret[i++] = str[j++];
	ret[i] = 0;
	return (ret);
}

void	add_var_utils(char *str, int **tab, char *s)
{
	int	i;

	i = 0;
	while (s[i] != 0)
		str[(*tab[1])++] = s[i++];
}

void	add_var(t_global *glb, char *str, char *ret, int **tab)
{
	t_envi	*temp;
	char	*var_name;
	char	*exit_s;

	temp = glb->env;
	exit_s = ft_itoa(glb->status);
	var_name = nume_var(str, tab[0]);
	if (var_name[0] == 0)
		add_var_utils(ret, tab, (char *)"$");
	else if (ft_strncmp(var_name, (char *)"?", 1) == SUCCESS)
		add_var_utils(ret, tab, exit_s);
	while (temp != NULL)
	{
		if (ft_strncmp(var_name, temp->var_name,
				ft_strlen(glb->env->var_name)) == SUCCESS)
			add_var_utils(ret, tab, temp->var_value);
		temp = temp->next;
	}
	free(var_name);
	free(exit_s);
}

void	add_to_next_quote(t_global *glb, char *str, char *ret, int **tab)
{
	char	c;

	c = str[(*tab[0])++];
	while (str[(*tab[0])] != 0 && str[*tab[0]] != c)
	{
		if (str[(*tab[0])] == '$' && c == DQUOTE)
			add_var(glb, str, ret, tab);
		else
			ret[(*tab[1])++] = str[(*tab[0])++];
	}
	(*tab[0])++;
}

char	*change_str(t_global *glb, char *str)
{
	char	ret[1024];
	int		**tab;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tab = (int **)malloc(sizeof(int *) * 2);
	if (!tab)
		return (NULL);
	tab[0] = &i;
	tab[1] = &j;
	while (str[i] != 0)
	{
		if (str[i] == SQUOTE || str[i] == DQUOTE)
			add_to_next_quote(glb, str, ret, tab);
		else if (str[i] == '$')
			add_var(glb, str, ret, tab);
		else
			ret[j++] = str[i++];
	}
	ret[j] = 0;
	free(tab);
	return (ft_strdup(ret));
}
