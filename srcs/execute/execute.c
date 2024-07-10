/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 19:28:09 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/07/10 21:48:13 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"

static void	execute_pipe(t_parser *cmd, t_env **env, char **paths, int dup_out);
static void	pipe_action(t_parser *cmd, t_env **env, char **paths, int dup_out);

bool	heredoc_check_loop(t_parser *parser, t_env **env)
{
	t_parser	*current;

	current = parser;
	if (current->file != NULL)
	{
		if (heredoc_loop(current->file, env) == false)
			return (false);
	}
	return (true);
}

void	execute(char *line, t_env **env, char **paths)
{
	t_token		*lexer_head;
	t_parser	*parser_head;
	t_parser	*current;

	if (line == NULL || env == NULL)
		return ;
	lexer_head = lexer(line);
	if (lexer_head == NULL)
		return ;
	parser_head = parser(lexer_head, env);
	free_lexer(lexer_head);
	if (parser_head == NULL)
		return ;
	current = parser_head;
	if (heredoc_check_loop(current, env) == false)
		return (free_parser(parser_head));
	while (current != NULL && current->next != NULL)
		current = current->next;
	execute_pipe(current, env, paths, 1);
	free_parser(parser_head);
}

static void	execute_pipe(t_parser *cmd, t_env **env, char **paths, int dup_out)
{
	if (dup_out != 1)
		dup2(dup_out, 1);
	if (cmd->prev != NULL)
		pipe_action(cmd, env, paths, dup_out);
	else
		execute_redirect(cmd, env, paths, (dup_out == 1));
}

static void	pipe_action(t_parser *cmd, t_env **env, char **paths, int dup_out)
{
	pid_t	pid;
	int		pipes[2];
	int		original_io[2];

	if (pipe(pipes) < 0)
		return ;
	if (save_io(&original_io[0]) < 0)
		return ;
	pid = safe_fork();
	if (pid == 0)
	{
		close(pipes[READ]);
		execute_pipe(cmd->prev, env, paths, pipes[WRITE]);
		close(pipes[WRITE]);
		exit(g_flag);
	}
	close(pipes[WRITE]);
	if (dup2(pipes[READ], 0) != 0)
		return (handle_status(pid, dup_out == 1));
	execute_redirect(cmd, env, paths, dup_out == 1);
	close(pipes[READ]);
	if (get_back_io(&original_io[0]) < 0)
		return (handle_status(pid, dup_out == 1));
	handle_status(pid, false);
}
