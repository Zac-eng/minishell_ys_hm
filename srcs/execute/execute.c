/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 19:28:09 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/06/13 20:06:37 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#define READ  (0)
#define WRITE (1)

static void	execute_pipe(t_parser *cmd, t_env **env, char **paths, int dup_out);
static int	control_stream(t_parser *cmd, int *pipes, int *stdin, int dup_out);

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
	int		pipes[2];
	int		original_stdin;
	int		pid;
	int		status;

	if (control_stream(cmd, &pipes[0], &original_stdin, dup_out) < 0)
		return ;
	if (cmd->prev != NULL)
	{
		pid = fork();
		if (pid < 0)
			put_error_exit("failed to fork");
		else if (pid == 0)
		{
			if (dup2(pipes[WRITE], 1) < 0)
				exit(1);
			execute_pipe(cmd->prev, env, paths, pipes[WRITE]);
			exit(0);
		}
		else
			handle_status(&status);
	}
	execute_redirect(cmd, env, paths);
	if (dup2(original_stdin, 0) < 0)
		exit(1);
}

static int	control_stream(t_parser *cmd, int *pipes, int *stdin, int dup_out)
{
	if (cmd == NULL || pipes == NULL || stdin == NULL)
		return (-1);
	*stdin = dup(0);
	if (*stdin < 0)
		exit(1);
	if (pipe(pipes) < 0)
		exit(1);
	if (dup_out != 1)
	{
		if (dup2(dup_out, 1) < 0)
			exit(1);
	}
	if (cmd->prev != NULL)
	{
		if (dup2(pipes[READ], 0) < 0)
			exit(1);
	}
	else
		close(pipes[READ]);
	return (0);
}
