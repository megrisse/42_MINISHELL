/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megrisse <megrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 15:25:42 by megrisse          #+#    #+#             */
/*   Updated: 2022/11/09 00:09:47 by megrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	handler(int sig)
{
	g_x = 128 + sig;
	printf("\n");
	//rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	ft_quit(int i)
{
	printf("Quit : %d\n", i);
	exit (i);
}

void	handler_sig(t_global *glb, int i)
{
	if (i == 0)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &handler);
		glb->status = g_x;
	}
	else
		signal(SIGQUIT, &ft_quit);
}
