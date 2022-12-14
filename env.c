/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:48:06 by hmeur             #+#    #+#             */
/*   Updated: 2022/11/07 12:30:38 by hameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

t_envi	*new_node(char *env_x)
{
	t_envi	*node;

	node = (t_envi *)malloc(sizeof(t_envi));
	if (!node)
		return (NULL);
	node->env_x = ft_strdup(env_x);
	node->var_name = name_var(env_x);
	node->var_value = value_var(env_x);
	node->next = NULL;
	return (node);
}

void	add_back(t_envi **envi, t_envi *new_node)
{
	t_envi	*temp;

	temp = *envi;
	if (temp == NULL)
	{
		*envi = new_node;
		return ;
	}
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = new_node;
	new_node->next = NULL;
}

void	add_front(t_envi **envi, t_envi *new_node)
{
	if (*envi == NULL)
	{
		*envi = new_node;
		return ;
	}
	new_node->next = *envi;
	*envi = new_node;
}

int	size_envi(t_envi *env)
{
	t_envi	*temp;
	int		i;

	i = 0;
	temp = env;
	while (temp != NULL && i++ > -1)
		temp = temp->next;
	return (i);
}

void	add_place(t_envi **envi, t_envi *new_node, int i)
{
	t_envi	*temp;
	int		size;

	temp = *envi;
	size = size_envi(*envi);
	while (temp->next->next != NULL && i < size)
		temp = temp->next;
	new_node->next = temp->next;
	temp->next = new_node;
}
