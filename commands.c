/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megrisse <megrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 20:36:27 by hmeur             #+#    #+#             */
/*   Updated: 2022/10/29 13:18:59 by megrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int	ft_pwd(t_cmnd *cmnd, t_envi **env)
{
	(void)cmnd;
	(void)env;
	char	pwd[1024];

	getcwd(pwd, 1024);
	printf("%s\n", pwd);
	ft_free(cmnd->cmnd);
	return (SUCCESS);
}

int ft_env(t_cmnd *cmnd, t_envi **env)
{
	t_envi *temp = *env;

	(void)cmnd;
	while (temp != NULL)
	{
		printf("%s=%s\n", temp->var_name, temp->var_value);
		temp = temp->next;
	}
	ft_free(cmnd->cmnd);
	return (SUCCESS);
}

int print_var(char *var)
{
	if (var[0] == '$')
		return (SUCCESS);
	return (FAILDE);
}

char *cherch_var(char *var, t_envi *env)
{
	int i;
	while (env != NULL)
	{
		i = 0;
		while (var[i] != 0 && env->env_x[i] == var[i])
			i++;
		if (var[i] == 0)
			return (env->env_x + i + 1);
		env = env->next;
	}
	return (NULL);
}

int ft_echo(t_cmnd *cmnd, t_envi **env)
{
	int i = 0;
	//check_using_echo without flage
	while (cmnd->cmnd[++i] != NULL)
	{
		/*_______check variables________*/
		if (print_var(cmnd->cmnd[i]) == SUCCESS)
			printf("%s ", cherch_var(cmnd->cmnd[i] + 1, *env));
		else
			printf("%s ", cmnd->cmnd[i]);
	}
	printf("\n");
	free(cmnd);
	return (SUCCESS);
}

int ft_exit(t_cmnd *cmnd, t_envi **env)
{
	(void)cmnd;
	(void)env;
	//change exit
	//ft_free(cmnd);
	printf("exit\n");
	//check_exit_value//
	exit(SUCCESS);
}

