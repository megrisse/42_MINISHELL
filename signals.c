/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hameur <hameur@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/30 15:25:42 by megrisse          #+#    #+#             */
/*   Updated: 2022/11/01 14:07:30 by hameur           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int x;

void handler(int sig)
{
    x = 127 + sig;
    printf("\n");
    //rl_replace_line("", 0);
    rl_on_new_line();
    rl_redisplay();
}

void    handler_sig(t_global *glb)
{
    signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, &handler);
    glb->status = x;
}