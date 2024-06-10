/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: h.miyazaki <h.miyazaki@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 10:21:14 by yususato          #+#    #+#             */
/*   Updated: 2024/06/10 19:40:42 by h.miyazaki       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	sigint_no_redisplay(int signum);
static void	free_envvars(t_env *tenv, char **paths);

int	main(int argc, char **argv, char **env)
{
	t_env		*tenv;
	char		**paths;
	char		*line;

	(void)argc, (void)argv;
	tenv = env_into_tenv(env);
	paths = get_paths();
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
			execute(line, &tenv, paths);
			free(line);
		}
	}
	free_envvars(tenv, paths);
	exit(0);
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
}

static void	free_envvars(t_env *tenv, char **paths)
{
	free_env(tenv);
	free_str_list(paths);
}
