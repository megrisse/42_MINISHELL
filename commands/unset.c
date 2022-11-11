/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 16:01:47 by hmeur             #+#    #+#             */
/*   Updated: 2022/11/10 14:46:07 by hameur           ###   ########.fr       */
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

void	unset_utils(t_envi *env, char *str)
{
	t_envi	*temp;
	int		i;

	i = 0;
	temp = env;
	while (temp != NULL && i++ >= 0)
	{
		if (ft_strncmp(temp->var_name, str,
				ft_strlen(temp->var_name)) == SUCCESS)
			break ;
		temp = temp->next;
	}
	if (temp != NULL)
		delete_node_env(&env, i - 1);
}

int	ft_unset(t_cmnd *cmnd, t_envi **env)
{
	int	j;

	j = 0;
	while (cmnd->cmnd[++j])
		unset_utils(*env, cmnd->cmnd[j]);
	return (SUCCESS);
}
