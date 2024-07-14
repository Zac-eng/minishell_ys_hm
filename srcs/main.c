/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 10:21:14 by yususato          #+#    #+#             */
/*   Updated: 2024/07/14 20:53:41 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigint_no_redisplay(int signum);

volatile sig_atomic_t	g_flag = 0;

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
		line = readline("minishell$ ");
		if (!line)
			minishell_exit(NULL);
		else
		{
			signal(SIGINT, sigint_no_redisplay);
			add_history(line);
			paths = get_paths(tenv);
			execute(line, &tenv, paths);
			rm_heredoc_file();
			free_str_list(paths);
			free(line);
		}
	}
	free_env(tenv);
	exit(g_flag);
}

static void	sigint_no_redisplay(int signum)
{
	if (signum == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}
