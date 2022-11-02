/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megrisse <megrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:01:47 by hmeur             #+#    #+#             */
/*   Updated: 2022/11/02 16:05:22 by megrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

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

int	change_var_value(t_envi *temp, char *name, char *value)
{
	char *ptr;

	//free(temp->env_x);
	free(temp->var_name);
	free(temp->var_value);
	ptr = ft_strlcat((char *)"=", value);
	temp->env_x = ft_strlcat(name, ptr);
	temp->var_value = ft_strdup(value);
	temp->var_name = ft_strdup(name);
	return (free(ptr), SUCCESS);
}

int	check_var(char *cmnd)
{
	int	i;

	i = 0;
	while (cmnd[i] != 0 && cmnd[i] != '=')
		i++;
	if (cmnd[i] == 0)
		return (FAILDE);
	return (SUCCESS);
}

int	ft_export(t_cmnd *cmnd, t_envi **env)
{
	char 	*name;
	char 	*value;
	t_envi	*temp;
	
	if (check_var(cmnd->cmnd[1]) != SUCCESS)
		return (FAILDE);
	name =  name_var(cmnd->cmnd[1]);
	temp = find_var(*env, name);
	if (temp != NULL)
	{
		free(temp->env_x);
		value = value_var(cmnd->cmnd[1]);
		change_var_value(temp, name, value);
		return (free(name), free(value), SUCCESS);
	}
	add_back(env, new_node(cmnd->cmnd[1]));
	return (free(name), SUCCESS);
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

