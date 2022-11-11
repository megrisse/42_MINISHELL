/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 20:23:51 by hmeur             #+#    #+#             */
/*   Updated: 2022/11/08 21:48:48 by hameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

char	*get_var(t_envi *env, char *str)
{
	t_envi	*temp;

	temp = env;
	while (temp != NULL)
	{
		if (ft_strncmp(str, temp->var_name, ft_strlen(str)) == SUCCESS)
			return (ft_strdup(temp->var_value));
		temp = temp->next;
	}
	return (NULL);
}

char	*check_cd_flags(t_envi *env, char *flag, char *var_name)
{
	char	*old_pwd;

	old_pwd = get_var(env, var_name);
	if (flag == NULL)
		flag = (char *)"~";
	if (old_pwd == NULL)
	{
		ft_putstr_fd(2, (char *)"cd: ");
		ft_putstr_fd(2, var_name);
		ft_putstr_fd(2, (char *)" not set\n");
	}
	else if (ft_strncmp(flag, (char *)"-", 1) == SUCCESS)
		printf("~%s\n", old_pwd);
	return (old_pwd);
}

char	*check_flags(t_envi *env, char *flag)
{
	char	*old_pwd;

	if (flag == NULL || ft_strncmp(flag, (char *)"~", 1) == SUCCESS)
		old_pwd = check_cd_flags(env, flag, (char *)"HOME");
	else if (ft_strncmp(flag, (char *)"-", 1) == SUCCESS)
		old_pwd = check_cd_flags(env, flag, (char *)"OLDPWD");
	else
		return (NULL);
	if (old_pwd != NULL)
		chdir(old_pwd);
	return (old_pwd);
}

int	is_flag(char *str)
{
	if (str == NULL)
		return (SUCCESS);
	else if (ft_strncmp(str, (char *)"-", 1) != SUCCESS)
		return (SUCCESS);
	else if (ft_strncmp(str, (char *)"~", 1) != SUCCESS)
		return (SUCCESS);
	return (FAILDE);
}

int	ft_cd(t_cmnd *cmnd, t_envi **env)
{
	char	*old_pwd;
	char	*o_pwd;
	char	pwd[1024];

	getcwd(pwd, 1024);
	old_pwd = ft_strdup(pwd);
	o_pwd = check_flags(*env, cmnd->cmnd[1]);
	if (o_pwd == NULL)
	{	
		if (chdir(cmnd->cmnd[1]) != SUCCESS)
		{
			if (is_flag(cmnd->cmnd[1]) != SUCCESS)
				printf("cd: no such file or directory: %s\n", cmnd->cmnd[1]);
			return (free(o_pwd), free(old_pwd), FAILDE);
		}
	}
	getcwd(pwd, 1024);
	change_var_value(find_var(*env, "OLDPWD"), (char *)"OLDPWD", old_pwd);
	change_var_value(find_var(*env, "PWD"), (char *)"PWD", pwd);
	return (free(o_pwd), free(old_pwd), SUCCESS);
}
