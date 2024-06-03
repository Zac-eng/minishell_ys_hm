/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 19:28:09 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/05/31 16:27:22 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#define READ  (0)
#define WRITE (1)

static void	execute_pipe(t_parser *cmd, t_env **env, char **paths, int dup_out);
static int	connect_pipe(int *pipes, int dup_out, int *original_stdin);

void	execute(t_parser *current, t_env **env, char **paths)
{
	if (current == NULL)
		return ;
	while (current != NULL && current->next != NULL)
		current = current->next;
	execute_pipe(current, env, paths, 1);
	// _env(*env);
}

static void	execute_pipe(t_parser *cmd, t_env **env, char **paths, int dup_out)
{
	int		pipes[2];
	int		pid;
	int		original_stdin;
	int		status;

	if (cmd == NULL || env == NULL || paths == NULL)
		return ;
	if (connect_pipe(&pipes[0], dup_out, &original_stdin) != 0)
		exit(1);
	if (cmd->prev != NULL)
	{
		pid = fork();
		if (pid < 0)
			put_error_exit("failed to fork");
		else if (pid == 0)
		{
			execute_pipe(cmd->prev, env, paths, pipes[WRITE]);
			exit(0);
		}
		else
			handle_status(&status);
	}
	execute_redirect(cmd, env, paths);
	dup2(original_stdin, 0);
	close(pipes[READ]);
}

static int	connect_pipe(int *pipes, int dup_out, int *original_stdin)
{
	if (dup_out != 1)
	{
		if (dup2(dup_out, 1) < 0)
			return (-1);
	}
	if (pipe(pipes) != 0)
		return (-1);
	*original_stdin = dup(0);
	if (*original_stdin < 0)
		return (-1);
	if (dup2(pipes[READ], 0) < 0)
		return (-1);
	return (0);
}
