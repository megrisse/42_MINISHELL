/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megrisse <megrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 20:23:51 by hmeur             #+#    #+#             */
/*   Updated: 2022/10/29 22:53:24 by megrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

char	*get_var(t_envi **env, char *str)
{
	t_envi *temp;

	temp = *env;
	while (temp != NULL)
	{
		if (ft_strncmp(str, temp->var_name, ft_strlen(str)) == SUCCESS)
			return (printf("<<%s>>\n", temp->var_value), ft_strdup(temp->var_value));
		temp = temp->next;
	}
	return (NULL);
}

int	ft_cd(t_cmnd *cmnd, t_envi **env)
{
	char 	*old_pwd;
	char 	*o_pwd;
	char	pwd[1024];

	getcwd(pwd, 1024);
	old_pwd = ft_strdup(pwd);
	if (cmnd->cmnd[1] == NULL)
	{
		o_pwd = get_var(env, "HOME");
		chdir(o_pwd);
		return (free(o_pwd), free(old_pwd), SUCCESS);
	}
	if (chdir(cmnd->cmnd[1]) != 0)
	{
		if (ft_strncmp(cmnd->cmnd[1] , "-", 1) == SUCCESS)
		{
			o_pwd = get_var(env, "OLDPWD");
			chdir(o_pwd);
			printf("~%s\n", o_pwd);
			return (free(o_pwd), free(old_pwd), SUCCESS);
		}
		printf("cd: no such file or directory: %s\n", cmnd->cmnd[1]);
		ft_free(cmnd->cmnd);
	}
	change_var_value(*env, "OLDPWD", old_pwd);
	change_var_value(*env, "PWD", pwd);
	return (free(old_pwd), SUCCESS);
}