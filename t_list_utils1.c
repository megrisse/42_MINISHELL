/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_list_utils1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megrisse <megrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/08 21:53:05 by megrisse          #+#    #+#             */
/*   Updated: 2022/11/08 22:25:19 by megrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	len_str(t_global *glb, char *str)
{
	int	i;
	int	ret;

	i = 0;
	ret = 0;
	while (str[i] != 0)
	{
		if (str[i] == DQUOTE || str[i] == SQUOTE)
			ret += fct(glb, str, &i, str[i]);
		else if (str[i] == '$')
			ret += fct2(glb, str, &i);
		else
			ret++;
		i++;
	}
	return (ret);
}

void	fct5(char *str, int **tab, char *s)
{
	int	i;

	i = 0;
	while (s[i] != 0)
		str[(*tab[1])++] = s[i++];
}

void	fct4(t_global *glb, char *str, char *ret, int **tab)
{
	t_envi	*temp;
	char	*exit_s;
	char	*var_name;

	temp = glb->env;
	exit_s = ft_itoa(glb->status);
	var_name = nume_var(str, tab[0]);
	if (var_name[0] == 0)
		fct5(ret, tab, (char *)"$");
	else if (ft_strncmp(var_name, (char *)"?", 1) == SUCCESS)
		fct5(ret, tab, exit_s);
	while (temp != NULL)
	{
		if (ft_strncmp(var_name, temp->var_name,
				ft_strlen(glb->env->var_name)) == SUCCESS)
			fct5(ret, tab, temp->var_value);
		temp = temp->next;
	}
	free(var_name);
	free(exit_s);
}

int	fct2(t_global *glb, char *s, int *i)
{
	t_envi	*temp;
	char	*exit_s;
	char	*var_name;
	int		len;

	temp = glb->env;
	var_name = nume_var(s, i);
	exit_s = ft_itoa(glb->status);
	len = ft_strlen(exit_s);
	if (ft_strncmp(var_name, (char *)"?", 1) == SUCCESS)
		return (free(var_name), free(exit_s), len);
	else if (var_name[0] == 0)
		return (free(var_name), free(exit_s), 1);
	while (temp != NULL)
	{
		if (ft_strncmp(var_name, temp->var_name,
				ft_strlen(glb->env->var_name)) == SUCCESS)
			return (free(var_name), free(exit_s),
				ft_strlen(glb->env->var_value));
		temp = temp->next;
	}
	return (free(var_name), free(exit_s), 0);
}

int	fct(t_global *glb, char *str, int *id, char c)
{
	int	i;

	(*id)++;
	i = 0;
	while (str[(*id)] != 0 && str[(*id)] != c)
	{
		if (str[(*id)] == '$' && c == DQUOTE)
			i += fct2(glb, str, id);
		else
		{
			i++;
			(*id)++;
		}
	}
	return (i);
}
