/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 19:28:09 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/06/16 22:01:38 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#define READ  (0)
#define WRITE (1)

static void	execute_pipe(t_parser *cmd, t_env **env, char **paths, int dup_out);
static int	control_stream(t_parser *cmd, int *pipes, int *io, int dup_out);
static void	get_back_io(int *original_io);

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
	while (current != NULL && current->next != NULL)
		current = current->next;
	execute_pipe(current, env, paths, 1);
	free_parser(parser_head);
}

static void	execute_pipe(t_parser *cmd, t_env **env, char **paths, int dup_out)
{
	pid_t	pid;
	int		pipes[2];
	int		original_io[2];

	if (control_stream(cmd, &pipes[0], &original_io[READ], dup_out) < 0)
		return ;
	if (cmd->prev != NULL)
	{
		pid = fork();
		if (pid < 0)
			put_error_exit(FORK_ERROR);
		else if (pid == 0)
		{
			close(pipes[READ]);
			execute_pipe(cmd->prev, env, paths, pipes[WRITE]);
			exit(0);
		}
		close(pipes[WRITE]);
		if (dup2(pipes[READ], 0) < 0)
			exit(1);
		execute_redirect(cmd, env, paths);
		handle_status(pid);
	}
	else
		execute_redirect(cmd, env, paths);
	get_back_io(&original_io[READ]);
}

static int	control_stream(t_parser *cmd, int *pipes, int *io, int dup_out)
{
	if (cmd == NULL || pipes == NULL || io == NULL)
		return (-1);
	io[READ] = dup(0);
	io[WRITE] = dup(1);
	if (io[READ] < 0 || io[WRITE] < 0)
		exit(1);
	if (pipe(pipes) < 0)
		exit(1);
	if (dup_out != 1)
	{
		if (dup2(dup_out, 1) < 0)
			exit(1);
	}
	if (cmd->prev == NULL)
	{
		close(pipes[READ]);
		close(pipes[WRITE]);
	}
	return (0);
}

static void	get_back_io(int *original_io)
{
	if (dup2(original_io[WRITE], 1) < 0)
		exit(1);
	if (dup2(original_io[READ], 0) < 0)
		exit(1);
}
