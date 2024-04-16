/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signalctrl.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 11:26:42 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/03/09 11:35:46 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

volatile sig_atomic_t	g_status = -1;

static void	sigint_handler(int signum);
static void	sigquit_handler(int signum);

void	signalctrl(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}

static void	sigint_handler(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_redisplay();
	}
	g_status = 1;
}

static void	sigquit_handler(int signum)
{
	if (signum == SIGQUIT)
		rl_on_new_line();
}
