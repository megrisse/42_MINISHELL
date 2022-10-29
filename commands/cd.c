/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megrisse <megrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 20:23:51 by hmeur             #+#    #+#             */
/*   Updated: 2022/10/29 13:19:58 by megrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"



char *get_oldpwd(t_envi *env)
{
	t_envi *temp;

	temp = env;
	while (temp != NULL)
	{
		if (ft_strncmp("OLDPWD", env->var_name, 6) == SUCCESS)
			return (ft_strdup(env->var_value));
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
	//check_path_(cmnd->cmnd[1]);
	//check_using cd without flags
	if (chdir(cmnd->cmnd[1]) != 0)
	{
		if (ft_strncmp(cmnd->cmnd[1] , "-", 1) == SUCCESS)
		{
			o_pwd = get_oldpwd(*env);
			chdir(o_pwd);
			printf("~%s\n", o_pwd);
			return (free(o_pwd), SUCCESS);
		}
		printf("cd: no such file or directory: %s\n", cmnd->cmnd[1]);
		ft_free(cmnd->cmnd);
	}
	change_var_value(*env, "OLDPWD", old_pwd);
	change_var_value(*env, "PWD", pwd);
	return (SUCCESS);
}