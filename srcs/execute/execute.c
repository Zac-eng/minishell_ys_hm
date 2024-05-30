/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 19:28:09 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/05/30 15:22:18 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#define READ  (0)
#define WRITE (1)

static void	execute_pipe(t_parser *cmd, t_env **env, char **paths, int dup_out);
static int	connect_pipe(int *pipes, int dup_out, int *original_stdin);

void	execute(char *line, t_env **env, char **paths)
{
	t_parser	*current;

	if (line == NULL || env == NULL || paths == NULL)
		exit(1);
	//instead of using parser, from here
	// test `echo test | cat > test1.txt < bad.c >> test2.txt`
	t_parser	parser1;
	t_parser	parser2;
	t_file		file1;
	t_file		file2;
	t_file		file3;
	char *cmd1[] = {"echo", "test", NULL};
	char *cmd2[] = {"wc", "-l", NULL};
	parser1.cmd = &cmd1[0];
	parser1.file = NULL;
	parser1.next = &parser2;
	// parser1.next = NULL;
	parser1.prev = NULL;
	parser2.cmd = &cmd2[0];
	parser2.file = &file1;
	parser2.next = NULL;
	parser2.prev = &parser1;
	file1.file_name = "test1.txt";
	file1.type = OUT_FILE;
	file2.file_name = "bad.c";
	file2.type = IN_FILE;
	file1.next = &file2;
	file3.file_name = "README.md";
	file3.type = IN_FILE;
	file2.next = &file3;
	file3.next = NULL;
	current = &parser1;
	//to here
	if (current == NULL)
		return ;
	while (current != NULL && current->next != NULL)
		current = current->next;
	execute_pipe(current, env, paths, 1);
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
