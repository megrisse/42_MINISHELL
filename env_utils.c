/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeur <hmeur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:47:10 by hameur            #+#    #+#             */
/*   Updated: 2022/09/29 01:22:37 by hmeur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"


char *name_var(char *env)
{
	int		i;
	int		j;
	char	*name = NULL;

	j = -1;
	i = 0;
	while(env[i] != 0 && env[i] != '=')
		i++;
	name = malloc(i + 1);
	while (env[++j] != '=')
		name[j] = env[j];
	name[j] = 0;
	return (name);
}

char *value_var(char *env)
{
	int i;

	i = 0;
	while(env[i] != 0 && env[i] != '=')
		i++;
	return (env + i + 1);
}

t_envi *init_envi(char **env)
{
	t_envi *envi;
	int	i;

	i = 0;
	while (env[i] != NULL)
		i++;
	envi = NULL;
	while(i > 0)
		add_front(&envi, new_node(ft_strdup(env[--i])));
	return(envi);
}

void    free_env(t_envi **env)
{
	t_envi *temp;

	temp = *env;
	while (temp != NULL)
	{
		*env = temp->next;
		free(temp->env_x);
		free(temp->var_name);
		free(temp);
		temp = *env;
	}
}

void delete_node_env(t_envi **env, int i)
{
	t_envi *temp = *env;
	while (temp != NULL && i-- > 1)
		temp = temp->next;
	if (temp == NULL)
		return ;
	t_envi *ptr = temp->next;
	temp->next = ptr->next;
	free(ptr);
}
