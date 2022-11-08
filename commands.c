/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megrisse <megrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 20:36:27 by hmeur             #+#    #+#             */
/*   Updated: 2022/11/08 18:26:53 by megrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_pwd(t_cmnd *cmnd, t_envi **env)
{
	char	pwd[1024];

	(void)cmnd;
	(void)env;
	getcwd(pwd, 1024);
	printf("%s\n", pwd);
	return (SUCCESS);
}

int	ft_env(t_cmnd *cmnd, t_envi **env)
{
	t_envi	*temp;

	(void)cmnd;
	temp = *env;
	while (temp != NULL)
	{
		if (temp->var_value != NULL)
			printf("%s=%s\n", temp->var_name, temp->var_value);
		temp = temp->next;
	}
	return (SUCCESS);
}

int	echo_flag(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	else
		return (FAILDE);
	while (str[i] != 0 && str[i] == 'n')
		i++;
	if (str[i] != 0)
		return (FAILDE);
	return (SUCCESS);
}

int	ft_echo(t_cmnd *cmnd, t_envi **env)
{
	int	i;
	int	key;

	i = 0;
	key = 0;
	(void)env;
	while (cmnd->cmnd[++i] != NULL)
	{
		if (echo_flag(cmnd->cmnd[i]) == SUCCESS)
			key = 1;
		else
			printf("%s ", cmnd->cmnd[i]);
	}
	if (key == 0)
		printf("\n");
	return (SUCCESS);
}

int	ft_exit(t_global *glb)
{
	int	i;

	i = glb->status;
	unlink(".heredoc");
	free_env(&glb->env);
	free(glb);
	printf("exit\n");
	exit(i);
}
