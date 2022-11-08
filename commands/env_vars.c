/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_vars.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megrisse <megrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:01:47 by hmeur             #+#    #+#             */
/*   Updated: 2022/11/09 00:10:17 by megrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int	change_var_value(t_envi *temp, char *name, char *value)
{
	char	*ptr;

	if (temp == NULL)
		return (FAILDE);
	free(temp->env_x);
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
	char	*name;
	char	*value;
	t_envi	*temp;
	int		i;

	i = 1;
	if (cmnd->cmnd[1] == NULL)
		return (print_ex(*env), SUCCESS);
	while (cmnd->cmnd[i])
	{
		if (check_var(cmnd->cmnd[i]) != SUCCESS)
			return (FAILDE);
		name = name_var(cmnd->cmnd[i]);
		temp = find_var(*env, name);
		if (temp != NULL)
		{
			value = value_var(cmnd->cmnd[i++]);
			change_var_value(temp, name, value);
			free(name);
			if (value != NULL)
				free(value);
			continue ;
		}
		add_back(env, new_node(cmnd->cmnd[i++]));
		free(name);
	}
	return (SUCCESS);
}

int	ft_unset(t_cmnd *cmnd, t_envi **env)
{
	int	j;

	j = 0;
	while (cmnd->cmnd[++j])
		unset_utils(*env, cmnd->cmnd[j]);
	return (SUCCESS);
}
