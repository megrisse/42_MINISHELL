/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: megrisse <megrisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 15:25:42 by megrisse          #+#    #+#             */
/*   Updated: 2022/11/08 20:05:51 by megrisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"


void handler(int sig)
{
    if (sig )
    x = 128 + sig;
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

void    handler_sig(t_global *glb, int i)
{
	if (i == 0)
	{
		signal(SIGQUIT, SIG_IGN);
		signal(SIGINT, &handler);
		glb->status = x;
	}
	else
		signal(SIGQUIT, &ft_quit);	
}