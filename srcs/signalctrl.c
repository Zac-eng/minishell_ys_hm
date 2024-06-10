/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signalctrl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 11:26:42 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/06/06 11:41:10 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_status = -1;

static void	sigint_redisplay(int signum);
static void	sigquit_handler(int signum);

void	signalctrl(void)
{
	rl_catch_signals = 0;
	signal(SIGINT, sigint_redisplay);
	signal(SIGQUIT, sigquit_handler);
}

static void	sigint_redisplay(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	g_status = 1;
}

static void	sigquit_handler(int signum)
{
	if (signum == SIGQUIT)
		rl_redisplay();
}
