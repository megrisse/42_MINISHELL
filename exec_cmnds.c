/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmnds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megrisse <megrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 22:46:29 by hmeur             #+#    #+#             */
/*   Updated: 2022/11/05 23:42:34 by megrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"


int	builtin_fct(t_cmnd *cmnd, t_global *glb)
{
	if (cmnd->cmnd[0] == NULL)
		return (FAILDE);
	if (ft_strncmp(cmnd->cmnd[0] ,(char *)"cd", 2) == SUCCESS)
		return(ft_cd(cmnd, &glb->env), SUCCESS);
	if (ft_strncmp(cmnd->cmnd[0] ,(char *)"pwd", 3) == SUCCESS)
		return(ft_pwd(cmnd, &glb->env), SUCCESS);
	if (ft_strncmp(cmnd->cmnd[0] ,(char *)"env", 3) == SUCCESS)
		return(ft_env(cmnd, &glb->env), SUCCESS);
	if (ft_strncmp(cmnd->cmnd[0] ,(char *)"echo", 4) == SUCCESS)
		return(ft_echo(cmnd, &glb->env), SUCCESS);
	if (ft_strncmp(cmnd->cmnd[0] ,(char *)"exit", 4) == SUCCESS)
		return (ft_exit(glb), SUCCESS);
	 if (ft_strncmp(cmnd->cmnd[0] ,(char *)"unset", 5) == SUCCESS)
	 	return(ft_unset(cmnd, &glb->env), SUCCESS);
	 if (ft_strncmp(cmnd->cmnd[0] ,(char *)"export", 6) == SUCCESS)
	 	return(ft_export(cmnd, &glb->env), SUCCESS);
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
	if (temp == NULL)
		return (NULL);
	char *str = remove_debut(temp->env_x, 5);
	paths = ft_split(str, ':');
	j = 0;
	free(str);
	return (paths);
}

int is_file(char *str)
{
	if (ft_strncmp(str, "./", 1) == SUCCESS)
		return (printf("***********\n"), FAILDE);
	return (SUCCESS);
}

int other_fct(t_cmnd *cmnd, t_envi **env)
{
	if (cmnd->cmnd[0] == NULL)
		return (FAILDE);
	if (access(cmnd->cmnd[0], X_OK) == SUCCESS)
		return (execve(cmnd->cmnd[0], cmnd->cmnd, cmnd->env));
	if (is_file(cmnd->cmnd[0]) != SUCCESS)
		return (FAILDE);
	char **paths = find_paths(env);
	if (paths == NULL)
		return (FAILDE);
	char *path_cmnd;
	char *ptr;
	//absolut path : /bin/ls
	ptr =  ft_strlcat((char *)"/", cmnd->cmnd[0]);
	int i = 0;
	while (paths[i] != NULL)
	{
		path_cmnd = ft_strlcat(paths[i++], ptr);
		if (access(path_cmnd, X_OK) == SUCCESS)
		{
			if (execve(path_cmnd, cmnd->cmnd, cmnd->env) < 0)
				return(printf("error f execve\n"), ft_free(paths), free(ptr), FAILDE);
			return (free(ptr), ft_free(paths), SUCCESS);
		}
		free(path_cmnd);
	}
	return (free(ptr), ft_free(paths), FAILDE);
}


void free_tcmnd(t_cmnd *cmnd)
{
	if (cmnd->cmnd != NULL)
		ft_free(cmnd->cmnd);
	if (cmnd->env != NULL)
		ft_free(cmnd->env);
	if (cmnd != NULL)
		free(cmnd);
}

int	exec_cmnd(t_list *cmnd_list, t_global *glb)
{
	t_cmnd *cmnd;
	int		red_type = 0;

	cmnd = initializ_cmnd(cmnd_list, glb->env);
	red_type = type_red(cmnd_list);
	if (red_type == R_OUT || red_type == DR_OUT)
		redirection_out(name_red(cmnd_list), red_type);
	else if (red_type == R_INP || red_type == DR_INP)
		redirection_inp(name_red(cmnd_list), red_type);
		
	if (builtin_fct(cmnd, glb) != SUCCESS)
	{
		if (other_fct(cmnd, &glb->env) != SUCCESS)
			return (ft_putstr_fd(2, cmnd->cmnd[0]), free_tcmnd(cmnd)
				, write(2 ,": command not found\n", 21), exit(127), FAILDE);//exit bwhd int
	}
	return (free_tcmnd(cmnd), exit(0), SUCCESS);
}

