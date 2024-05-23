/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 10:21:14 by yususato          #+#    #+#             */
/*   Updated: 2024/05/23 21:26:58 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_envvars(t_env *tenv, char **paths);

int	main(int argc, char **argv, char **env)
{
	t_env	*tenv;
	char	**paths;
	char	*line;

	(void)argc, (void)argv;
	signalctrl();
	tenv = env_into_tenv(env);
	paths = get_paths();
	while (true)
	{
		line = readline("> ");
		if (!line)
			break ;
		else
		{
			add_history(line);
			execute(line, &tenv, paths);
			free(line);
		}
	}
	free_envvars(tenv, paths);
	rl_clear_history();
	exit(0);
}
// __attribute((destructor)) static void destructor() {
// 	system("leaks -q minishell");
// }

static void	free_envvars(t_env *tenv, char **paths)
{
	free_env(tenv);
	free_str_list(paths);
}
