/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 16:47:10 by hameur            #+#    #+#             */
/*   Updated: 2022/11/10 19:13:31 by hameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*name_var(char *env)
{
	int		i;
	int		j;
	char	*name;

	name = NULL;
	j = -1;
	i = 0;
	while (env[i] != 0 && env[i] != '=')
		i++;
	name = (char *)malloc(i + 1);
	if (!name)
		return (NULL);
	while (env[++j] != '=')
		name[j] = env[j];
	name[j] = 0;
	return (name);
}

char	*value_var(char *env)
{
	char	*ptr;
	int		i;

	i = 0;
	while (env[i] != 0 && env[i] != '=')
		i++;
	ptr = env + i + 1;
	return (ft_strdup(ptr));
}

t_envi	*init_envi(char **env)
{
	t_envi	*envi;
	int		i;

	i = 0;
	while (env[i] != NULL)
		i++;
	envi = NULL;
	while (i > 0)
		add_front(&envi, new_node(env[--i]));
	return (envi);
}

void	delete_node_env(t_envi **env, int i)
{
	t_envi	*temp;
	t_envi	*ptr;

	temp = *env;
	while (temp != NULL && i-- > 1)
		temp = temp->next;
	if (temp == NULL)
		return ;
	ptr = temp->next;
	temp->next = ptr->next;
	ptr->next = NULL;
	free(ptr->env_x);
	free(ptr->var_name);
	free(ptr->var_value);
	free(ptr);
}
