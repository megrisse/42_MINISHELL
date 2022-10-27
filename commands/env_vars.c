/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeur <hmeur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:01:47 by hmeur             #+#    #+#             */
/*   Updated: 2022/09/30 13:25:12 by hmeur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

t_envi *find_var(t_envi *env, char *name)
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

int change_var_value(t_envi *env,char *name, char *value)
{
	t_envi *temp;

	temp = find_var(env, name);
	if (temp == NULL)
		return (FAILDE);
	free(temp->env_x);
	temp->env_x = ft_strlcat(temp->var_name, ft_strlcat("=", value));
	temp->var_value = value;
	return (SUCCESS);
}

int check_var(char *cmnd)
{
	int i = 0;
	while (cmnd[i] != 0 && cmnd[i] != '=')
		i++;
	if (cmnd[i] == 0)
		return (FAILDE);
	return (SUCCESS);
}

int ft_export(t_cmnd *cmnd, t_envi **env)
{
	int i = size_envi(*env);
	if (check_var(cmnd->cmnd[1]) != SUCCESS)
		return (FAILDE);
	if (find_var(*env, name_var(cmnd->cmnd[1])) != NULL)
	{
		change_var_value(*env, name_var(cmnd->cmnd[1]), value_var(cmnd->cmnd[1]));
		return (SUCCESS);
	}
	add_back(env, new_node(cmnd->cmnd[1]));
	return (SUCCESS);
}


int ft_unset(t_cmnd *cmnd, t_envi **env)
{
	t_envi *temp = *env;
	int i = 0;
	while (temp != NULL && i++ >= 0)
	{
		if (ft_strncmp(temp->env_x, cmnd->cmnd[1], ft_strlen(cmnd->cmnd[1] - 1)) == SUCCESS)
		{
			delete_node_env(env, i - 1);
			break ;
		}
		temp = temp->next;
	}
	return (SUCCESS);
}

