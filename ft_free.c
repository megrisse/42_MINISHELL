/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 14:48:48 by hameur            #+#    #+#             */
/*   Updated: 2022/11/10 19:13:14 by hameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	free_env(t_envi **env)
{
	t_envi	*temp;

	temp = *env;
	while (temp != NULL)
	{
		*env = temp->next;
		free(temp->env_x);
		free(temp->var_name);
		free(temp->var_value);
		free(temp);
		temp = *env;
	}
}

void	free_tcmnd(t_cmnd *cmnd)
{
	if (cmnd->cmnd != NULL)
		ft_free(cmnd->cmnd);
	if (cmnd->env != NULL)
		ft_free(cmnd->env);
	if (cmnd != NULL)
		free(cmnd);
}

void	free_list(t_list **root, t_list *node)
{
	if (node == NULL)
		return ;
	free_list(root, node->next);
	free(node->str);
	free(node);
}

void	ft_free(char **str)
{
	int	i;

	if (str == NULL)
		return ;
	i = -1;
	while (str[++i])
		free(str[i]);
	free(str);
}
