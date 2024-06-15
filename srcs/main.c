/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 10:21:14 by yususato          #+#    #+#             */
/*   Updated: 2024/06/15 10:37:10 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigint_no_redisplay(int signum);

volatile sig_atomic_t	g_status = 0;

int	main(int argc, char **argv, char **env)
{
	t_env		*tenv;
	char		**paths;
	char		*line;

	(void)argc, (void)argv;
	tenv = env_into_tenv(env);
	while (true)
	{
		signalctrl();
		line = readline("minishell > ");
		if (!line)
			break ;
		else
		{
			signal(SIGINT, sigint_no_redisplay);
			add_history(line);
			paths = get_paths(tenv);
			execute(line, &tenv, paths);
			free_str_list(paths);
			free(line);
		}
	}
	free_env(tenv);
	exit(g_status);
}
// __attribute((destructor)) static void destructor() {
// 	system("leaks -q minishell");
// }

static void	sigint_no_redisplay(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
	g_status = 1;
}
