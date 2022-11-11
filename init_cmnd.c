/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cmnd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 19:48:42 by hmeur             #+#    #+#             */
/*   Updated: 2022/11/10 16:25:35 by hameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	**init_cmnd_table(t_list *cmnd, int size)
{
	t_list	*temp;
	char	**comnd;
	int		i;

	temp = cmnd;
	i = 0;
	comnd = (char **)malloc(sizeof(char *) * size);
	if (!comnd)
		return (NULL);
	if (temp->type != WORD && check_red_name(temp->str) == FAILDE)
		temp = temp->next->next;
	else if (temp->type != WORD && check_red_name(temp->str) == SUCCESS)
		temp = temp->next;
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
	if (temp != NULL && temp->type != WORD && temp->type != PIPE
		&& check_red_name(temp->str) == FAILDE)
		temp = temp->next->next;
	else if (temp != NULL && temp->type != WORD
		&& temp->type != PIPE && check_red_name(temp->str) == SUCCESS)
		temp = temp->next;
	while (temp != NULL && temp->type == WORD && i++ > -1)
		temp = temp->next;
	cmnd->cmnd = init_cmnd_table(cmnd_list, i + 1);
	cmnd->env = init_env_table(env, size_envi(env) + 1);
	return (cmnd);
}
