/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 19:28:09 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/05/23 20:10:01 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#define READ  (0)
#define WRITE (1)

static void	execute_pipe(t_parser *cmd, t_env **env, char **paths, int dup_out);
static void	execute_redirect(t_parser *cmd, t_env **env, char **paths);
static int	connect_pipe(int *pipes, int dup_out, int *original_stdin);

void	execute(char *line, t_env **env, char **paths)
{
	t_parser	*current;

	if (line == NULL || env == NULL)
		exit(1);
	//instead of using parser, from here
	t_parser	parser1;
	t_parser	parser2;
	t_file		file1;
	t_file		file2;
	t_file		file3;
	char *cmd1[] = {"export", "test=test", NULL};
	char *cmd2[] = {"ls", NULL};
	parser1.cmd = &cmd1[0];
	parser1.file = NULL;
	parser1.next = &parser2;
	parser1.prev = NULL;
	parser2.cmd = &cmd2[0];
	parser2.file = &file1;
	parser2.next = NULL;
	parser2.prev = &parser1;
	file1.file_name = "./test1.txt";
	file1.type = OUT_FILE;
	file2.file_name = "./test2.txt";
	file2.type = OUT_FILE;
	file1.next = &file2;
	file3.file_name = "./test3.txt";
	file3.type = OUT_FILE;
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

	if (cmd == NULL || env == NULL)
		return ;
	if (connect_pipe(&pipes[0], dup_out, &original_stdin) != 0)
		exit(0);
	if (cmd->prev == NULL)
		return (execute_redirect(cmd, env, paths));
	pid = fork();
	if (pid < 0)
		put_error_exit("failed to fork");
	else if (pid == 0)
	{
		execute_pipe(cmd->prev, env, paths, pipes[WRITE]);
		exit(0);
	}
	else
	{
		handle_status(&status);
		execute_redirect(cmd, env, paths);
		dup2(original_stdin, 0);
	}
}

static void	execute_redirect(t_parser *cmd, t_env **env, char **paths)
{
	t_file	*current_file;
	int		std_out;
	int		fd;

	if (cmd == NULL || env == NULL)
		return ;
	if (cmd->file == NULL)
		return (execute_cmd(cmd->cmd, env, paths));
	current_file = cmd->file;
	std_out = dup(1);
	if (std_out < 0)
		exit(1);
	while (current_file != NULL)
	{
		fd = open(current_file->file_name, O_RDWR);
		if (fd < 0)
			exit(1);
		if (dup2(fd, 1) < 0)
			exit(1);
		execute_cmd(cmd->cmd, env, paths);
		current_file = current_file->next;
	}
	if (dup2(std_out, 1) < 0)
		exit(1);
}

static int	connect_pipe(int *pipes, int dup_out, int *original_stdin)
{
	if (dup_out != 1)
	{
		if (dup2(dup_out, 1) < 0)
			return (-1);
		printf("duped");
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
