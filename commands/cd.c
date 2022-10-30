/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megrisse <megrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 20:23:51 by hmeur             #+#    #+#             */
/*   Updated: 2022/10/30 15:03:11 by megrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

char	*get_var(t_envi *env, char *str)
{
	t_envi *temp;

	temp = env;
	while (temp != NULL)
	{
		if (ft_strncmp(str, temp->var_name, ft_strlen(str)) == SUCCESS)
			return (ft_strdup(temp->var_value));
		temp = temp->next;
	}
	return (NULL);
}

char *check_flags(t_envi *env, char *flag)
{
	char *old_pwd;
	
	if (flag == NULL)
		old_pwd = get_var(env, "HOME");
	else if (ft_strncmp(flag , "-", 1) == SUCCESS)
	{
		old_pwd = get_var(env, "OLDPWD");
		printf("~%s\n", old_pwd);
	}
	else if (ft_strncmp(flag , "~", 1) == SUCCESS)
		old_pwd = get_var(env, "HOME");
	else
		return (NULL);
	chdir(old_pwd);
	return (old_pwd);
}

int	ft_cd(t_cmnd *cmnd, t_envi **env)
{
	char 	*old_pwd;
	char 	*o_pwd;
	char	pwd[1024];

	getcwd(pwd, 1024);
	old_pwd = ft_strdup(pwd);
	o_pwd = check_flags(*env, cmnd->cmnd[1]);
	if (o_pwd == NULL)
	{	
		if (chdir(cmnd->cmnd[1]) != SUCCESS)
		{
			printf("cd: no such file or directory: %s\n", cmnd->cmnd[1]);
			return (ft_free(cmnd->cmnd), FAILDE);
		}
	}
	change_var_value(*env, "OLDPWD", old_pwd);
	change_var_value(*env, "PWD", ft_strdup(getcwd(pwd, 1024)));
	return (SUCCESS);
}