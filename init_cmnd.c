/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmnd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megrisse <megrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 19:48:42 by hmeur             #+#    #+#             */
/*   Updated: 2022/11/08 23:40:00 by megrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	**init_cmnd_table(t_list *cmnd, int size)
{
	char	**comnd;
	t_list	*temp;
	int		i;

	temp = cmnd;
	comnd = (char **)malloc(sizeof(char *) * size);
	i = 0;
	if (!comnd)
		return (NULL);
	if (temp->type != WORD)
		temp = temp->next->next;
	while (temp != NULL && temp->type == WORD)
	{
		comnd[i++] = ft_strdup(temp->str);
		temp = temp->next;
	}
	comnd[i] = NULL;
	return (comnd);
}

char	**init_env_table(t_envi *envi, int size)
{
	t_envi	*temp;
	char	**env;
	int		i;

	temp = envi;
	env = (char **)malloc(sizeof(char *) * size);
	if (!env)
		return (NULL);
	i = 0;
	while (temp != NULL)
	{
		env[i++] = ft_strdup(temp->env_x);
		temp = temp->next;
	}
	env[i] = NULL;
	return (env);
}

t_cmnd	*initializ_cmnd(t_list *cmnd_list, t_envi *env)
{
	t_cmnd	*cmnd;
	t_list	*temp;
	int		i;

	cmnd = (t_cmnd *)malloc(sizeof(t_cmnd));
	if (!cmnd)
		return (NULL);
	temp = cmnd_list;
	i = 0;
	if (temp != NULL && temp->type != WORD && temp->type != PIPE)
		temp = temp->next->next;
	while (temp != NULL && temp->type == WORD && i++ > -1)
		temp = temp->next;
	cmnd->cmnd = init_cmnd_table(cmnd_list, i + 1);
	cmnd->env = init_env_table(env, size_envi(env) + 1);
	return (cmnd);
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
