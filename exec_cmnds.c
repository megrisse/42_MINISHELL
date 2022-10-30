/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmnds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megrisse <megrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 22:46:29 by hmeur             #+#    #+#             */
/*   Updated: 2022/10/30 18:37:05 by megrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"


int builtin_fct(t_cmnd *cmnd, t_envi **env)
{
	if (ft_strncmp(cmnd->cmnd[0] , (char *)"cd", 2) == SUCCESS)
		return(ft_cd(cmnd, env), SUCCESS);
	if (ft_strncmp(cmnd->cmnd[0] , (char *)"pwd", 3) == SUCCESS)
		return(ft_pwd(cmnd, env), SUCCESS);
	if (ft_strncmp(cmnd->cmnd[0] , (char *)"env", 3) == SUCCESS)
		return(ft_env(cmnd, env), SUCCESS);
	if (ft_strncmp(cmnd->cmnd[0] , (char *)"echo", 4) == SUCCESS)
		return(ft_echo(cmnd, env), SUCCESS);
	if (ft_strncmp(cmnd->cmnd[0] , (char *)"exit", 4) == SUCCESS)
		return (ft_exit(cmnd, env), SUCCESS);
	 if (ft_strncmp(cmnd->cmnd[0] , (char *)"unset", 5) == SUCCESS)
	 	return(ft_unset(cmnd, env), SUCCESS);
	 if (ft_strncmp(cmnd->cmnd[0] , (char *)"export", 6) == SUCCESS)
	 	return(ft_export(cmnd, env), SUCCESS);
	return (FAILDE);
}

char *remove_debut(char* s, int i)
{
	int j = 0;
	char *str;

	str = (char *)malloc(ft_strlen(s) - i + 1);
	while (s[i] != 0)
		str[j++] = s[i++];
	str[j] = 0;
	return (str);
}

char **find_paths(t_envi **env)
{
	int i = 0;
	int j = 1;
	t_envi *temp = *env;
	char **paths;
	while (temp != NULL)
	{
		j = ft_strncmp(temp->env_x, (char *)"PATH=", 4);
		if (j == 0)
			break;
		temp = temp->next;
	}
	char *str = remove_debut(temp->env_x, 5);
	paths = ft_split(str, ':');
	return (free(str), paths);
}



int other_fct(t_cmnd *cmnd, t_envi **env)
{
	char **paths = find_paths(env);
	char *path_cmnd;
	char *ptr;
	ptr =  ft_strlcat((char *)"/", cmnd->cmnd[0]);
	int i = 0;
	int j;
	while (paths[i] != NULL)
	{
		path_cmnd = ft_strlcat(paths[i++], ptr);
		if (access(path_cmnd, F_OK) == SUCCESS)
		{
			//absolut path : /bin/ls
			j = execve(path_cmnd, cmnd->cmnd, cmnd->env);
			if (j < 0)
				return(printf("error f execve\n"), ft_free(paths), FAILDE);
			return (free(ptr), ft_free(paths), SUCCESS);
		}
		free(path_cmnd);
	}
	return (free(ptr), FAILDE);
}


int	exec_cmnd(t_list *cmnd_list, t_envi *env)
{
	t_cmnd *cmnd;
	int		red_type = 0;

	cmnd = initializ_cmnd(cmnd_list, env);
	red_type = type_red(cmnd_list);
	if (red_type == R_OUT || red_type == DR_OUT)
		redirection_out(name_red(cmnd_list), red_type);
	else if (red_type == R_INP || red_type == DR_INP)
		redirection_inp(name_red(cmnd_list), red_type);
	if (builtin_fct(cmnd, &env) != SUCCESS)
	{
		if (other_fct(cmnd, &env) != SUCCESS)
			return (ft_free(cmnd->cmnd), ft_putstr_fd(2, cmnd->cmnd[0]), write(2 ,": command not found\n", 21), exit(127), FAILDE);//exit bwhd int
	}
	return (ft_free(cmnd->cmnd), exit(0), SUCCESS);
}

