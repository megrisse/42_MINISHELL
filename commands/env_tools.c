/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megrisse <megrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 00:01:31 by megrisse          #+#    #+#             */
/*   Updated: 2022/11/09 00:06:58 by megrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

void	print_ex(t_envi *env)
{
	while (env != NULL)
	{
		printf("declare -x %s\n", env->env_x);
		env = env->next;
	}
}

t_envi	*find_var(t_envi *env, char *name)
{
	t_envi	*temp;

	temp = env;
	while (temp != NULL)
	{
		if (ft_strncmp(temp->var_name, name, ft_strlen(name)) == 0)
			return (temp);
		temp = temp->next;
	}
	return (NULL);
}

void	unset_utils(t_envi *env, char *str)
{
	t_envi	*temp;
	int		i;

	temp = env;
	i = 0;
	while (temp != NULL && i++ >= 0)
	{
		if (ft_strncmp(temp->var_name, str,
				ft_strlen(temp->var_name)) == SUCCESS)
		{
			delete_node_env(&env, i - 1);
			break ;
		}
		temp = temp->next;
	}
}
