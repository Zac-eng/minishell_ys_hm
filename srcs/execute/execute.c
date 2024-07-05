/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 19:28:09 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/07/05 16:58:13 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#define READ  (0)
#define WRITE (1)

static void	execute_pipe(t_parser *cmd, t_env **env, char **paths, int dup_out);
static int	control_stream(t_parser *cmd, int *pipes, int *io, int dup_out);
static void	get_back_io(int *original_io, int *pipes);

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
		pid = safe_fork();
		if (pid == 0)
		{
			close(pipes[READ]);
			execute_pipe(cmd->prev, env, paths, pipes[WRITE]);
			exit(g_flag);
		}
		close(pipes[WRITE]);
		if (dup2(pipes[READ], 0) != 0)
			return (handle_status(pid, dup_out == 1));
		execute_redirect(cmd, env, paths, dup_out == 1);
		get_back_io(&original_io[READ], &pipes[0]);
		ft_printf("pid:%d  %s\n", pid, cmd->cmd[0]);
		handle_status(pid, false);
	}
	else
	{
		execute_redirect(cmd, env, paths, dup_out == 1);
		get_back_io(&original_io[READ], &pipes[0]);
	}
}

static int	control_stream(t_parser *cmd, int *pipes, int *io, int dup_out)
{
	if (cmd == NULL || pipes == NULL || io == NULL)
		return (-1);
	io[READ] = dup(0);
	io[WRITE] = dup(1);
	if (io[READ] < 0 || io[WRITE] < 0)
	{
		perror_set_flag();
		return (-1);
	}
	if (pipe(pipes) < 0)
	{
		perror_set_flag();
		return (-1);
	}
	if (dup_out != 1)
	{
		if (dup2(dup_out, 1) < 0)
			perror_set_flag();
	}
	if (cmd->prev == NULL)
	{
		close(pipes[READ]);
		close(pipes[WRITE]);
	}
	return (0);
}

static void	get_back_io(int *original_io, int *pipes)
{
	if (dup2(original_io[WRITE], 1) < 0)
		perror_set_flag();
	if (dup2(original_io[READ], 0) < 0)
		perror_set_flag();
	close(pipes[READ]);
	close(pipes[WRITE]);
}
