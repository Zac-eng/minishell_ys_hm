/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signalctrl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 11:26:42 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/06/18 21:20:35 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	g_flag = 1;
}

static void	sigquit_handler(int signum)
{
	(void)signum;
}
