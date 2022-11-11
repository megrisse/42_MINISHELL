/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_cmnds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/26 22:46:29 by hmeur             #+#    #+#             */
/*   Updated: 2022/11/10 19:09:49 by hameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*remove_debut(char *s, int i)
{
	char	*str;
	int		j;

	str = (char *)malloc(ft_strlen(s) - i + 1);
	j = 0;
	if (!str)
		return (NULL);
	while (s[i] != 0)
		str[j++] = s[i++];
	str[j] = 0;
	return (str);
}

char	**find_paths(t_envi **env)
{
	char	**paths;
	t_envi	*temp;
	char	*str;
	int		j;

	paths = NULL;
	str = NULL;
	temp = *env;
	j = 1;
	while (temp != NULL)
	{
		j = ft_strncmp(temp->env_x, (char *)"PATH=", 4);
		if (j == 0)
			break ;
		temp = temp->next;
	}
	if (temp == NULL)
		return (NULL);
	str = remove_debut(temp->env_x, 5);
	paths = ft_split(str, ':');
	j = 0;
	free(str);
	return (paths);
}

int	other_utils(char **paths, t_cmnd *cmnd, char *ptr)
{
	char	*path_cmnd;
	int		i;

	i = 0;
	while (paths[i] != NULL)
	{
		path_cmnd = ft_strlcat(paths[i++], ptr);
		if (access(path_cmnd, X_OK) == SUCCESS)
		{
			if (execve(path_cmnd, cmnd->cmnd, cmnd->env) < 0)
				return (printf("error\n"), ft_free(paths), free(ptr), FAILDE);
			return (free(ptr), ft_free(paths), SUCCESS);
		}
		free(path_cmnd);
	}
	return (print_error(cmnd->cmnd[0], 1), free(ptr), ft_free(paths), FAILDE);
}

int	other_fct(t_cmnd *cmnd, t_envi **env)
{
	char	**paths;
	char	*ptr;

	if (cmnd->cmnd[0] == NULL)
		return (FAILDE);
	if (access(cmnd->cmnd[0], X_OK) == SUCCESS)
		return (execve(cmnd->cmnd[0], cmnd->cmnd, cmnd->env));
	if (is_file(cmnd->cmnd[0]) != SUCCESS)
		return (print_error(cmnd->cmnd[0], 0), FAILDE);
	paths = find_paths(env);
	if (paths == NULL)
		return (print_error(cmnd->cmnd[0], 1), FAILDE);
	ptr = ft_strlcat((char *)"/", cmnd->cmnd[0]);
	return (other_utils(paths, cmnd, ptr));
}

int	exec_cmnd(t_list *cmnd_list, t_global *glb)
{
	t_cmnd	*cmnd;
	int		red_type;

	red_type = 0;
	cmnd = initializ_cmnd(cmnd_list, glb->env);
	red_type = type_red(cmnd_list);
	if (red_type == R_OUT || red_type == DR_OUT)
		redirection_out(name_red(cmnd_list), red_type);
	else if (red_type == R_INP || red_type == DR_INP)
		redirection_inp(name_red(cmnd_list), red_type);
	if (builtin_fct(cmnd, glb) != SUCCESS)
	{
		if (other_fct(cmnd, &glb->env) != SUCCESS)
			return (free_tcmnd(cmnd), exit(127), FAILDE);
	}
	return (free_tcmnd(cmnd), exit(0), SUCCESS);
}
