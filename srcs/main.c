/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 10:21:14 by yususato          #+#    #+#             */
/*   Updated: 2024/06/06 11:41:44 by hmiyazak         ###   ########.fr       */
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

// int	main(int argc, char **argv, char **env)
// {
// 	t_env	*tenv;
// 	char	*line;
// 	t_token *lexer_head;
// 	t_parser *parser_head;

// 	(void)argc;
// 	(void)argv;
// 	// signalctrl();
// 	tenv = env_into_tenv(env);
// 	while (true)
// 	{
// 		line = readline("> ");
// 		if (!line)
// 			break ;
// 		if (line)
// 		{
// 			lexer_head = lexer(line);
// 			parser_head = parser(lexer_head);
// 			int i =0;
// 			int a = 0;
// 			int j = 0;
// 			while (parser_head->next != NULL)
// 			{
// 			parser_head = parser_head->next;
// 			}
// 			while (parser_head != NULL)
// 			{
// 				printf("parser->pointer:%p\n",parser_head );
// 				while (parser_head->cmd[i] != NULL)
// 			{
// 				printf("cmd:%s\n",parser_head->cmd[i] );
// 				i++;
// 			}
// 			while (parser_head->file != NULL)
// 			{
// 				printf("filename:%s\n",parser_head->file->file_name );
// 				parser_head->file = parser_head->file->next;
// 			}
// 			a++;
// 			i=0;
// 			parser_head = parser_head->prev;
// 			}
// 			add_history(line);
// 			// execute(line, &tenv);
// 			free(line);
// 		}
// 	}
// 	exit(0);
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
