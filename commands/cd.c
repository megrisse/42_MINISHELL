/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmeur <hmeur@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 20:23:51 by hmeur             #+#    #+#             */
/*   Updated: 2022/09/30 13:17:51 by hmeur            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"



int	ft_cd(t_cmnd *cmnd, t_envi **env)
{
	char *old_pwd;

	old_pwd = getcwd(NULL, 0);
	//check_path_(cmnd->cmnd[1]);
	//check_using cd without flage
	if (chdir(cmnd->cmnd[1]) != 0)
	{
		printf("cd: no such file or directory: %s\n", cmnd->cmnd[1]);
		exit(1);//ft_free(cmnd->cmnd);
	}
	change_var_value(*env, "OLDPWD", old_pwd);
	change_var_value(*env, "PWD", getcwd(NULL, 0));
	return (SUCCESS);
	//exit(0);
}

