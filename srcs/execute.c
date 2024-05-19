/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 19:28:09 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/05/19 14:05:26 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#define READ  (0)
#define WRITE (1)

static void	execute_pipe(t_parser *cmd, t_env **env, int dup_out);
static void	execute_redirect(t_parser *cmd, t_env **env);
static void	execute_cmd(char **cmd, t_env **env);
static int	connect_pipe(int *pipes, int dup_out, int *original_stdin);

void	execute(char *line, t_env **env)
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
	char *cmd2[] = {"env", NULL};
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
	execute_pipe(current, env, 1);
	// signal(SIGINT, sigexit);
	// while (current != NULL)
	// {
	// 	if (current->next != NULL)
	// 		execute_pipe(current, env, 0);
	// 	else if (current->file != NULL)
	// 		execute_redirect(current, env);
	// 	else
	// 		execute_cmd(current->cmd, env);
	// 	current = current->next;
	// 	_env(*env);
	// }
	// exit(0);
}

static void	execute_pipe(t_parser *cmd, t_env **env, int dup_out)
{
	int		pipes[2];
	int		pid;
	int		original_stdin;
	int		status;
	char	buffer[1024];

	if (cmd == NULL || env == NULL)
		return ;
	if (connect_pipe(&pipes[0], dup_out, &original_stdin) != 0)
		exit(0);
	if (cmd->prev == NULL)
		return (execute_redirect(cmd, env));
	pid = fork();
	if (pid < 0)
		put_error_exit("failed to fork");
	else if (pid == 0)
	{
		execute_pipe(cmd->prev, env, pipes[WRITE]);
		exit(0);
	}
	else
	{
		handle_status(&status);
		read(pipes[READ], buffer, 5);
		buffer[5] = '\0';
		printf("childout; %s", buffer);
		execute_redirect(cmd, env);
		dup2(original_stdin, 0);
		printf("returned");
	}
}

static void	execute_redirect(t_parser *cmd, t_env **env)
{
	t_file	*current_file;
	int		std_out;
	int		fd;

	if (cmd == NULL || env == NULL)
		return ;
	std_out = 1;
	if (cmd->file == NULL)
		return (execute_cmd(cmd->cmd, env));
	current_file = cmd->file;
	while (current_file != NULL)
	{
		fd = open(current_file->file_name, O_RDWR);
		if (fd < 0)
			exit(1);
		dup2(fd, std_out);
		close(std_out);
		std_out = fd;
		execute_cmd(cmd->cmd, env);
		current_file = current_file->next;
	}
}
	// if (pipe(pipes) < 0)
	// 	return ;
	// while (true)
	// {
	// 	printf("abc\n");
	// 	usleep(1000000);
	// }
	// pid = fork();
	// printf("forked execute\n");
	// if (pid < 0)
	// 	exit(1);
	// else if (pid == 0)
	// {
	// 	dup2(pipes[WRITE], 1);
	// 	printf("called");
	// 	exit(0);
	// }
	// else
	// {
	// 	dup2(pipes[READ], 0);
	// 	read(0, buf, 4);
	// 	buf[4] = '\0';
	// 	printf("%d, %s\n", getpid(), buf);
	// 	wait(&status);
	// 	exit(status);
	// }


// int	main(void)
// {
// 	char *cmd[] = {"ls", "-a"};

// 	execute(&cmd[0], PIPE);
// 	return (0);
// }

static void	execute_cmd(char **cmd, t_env **env)
{
	if (cmd == NULL || env == NULL)
		return ;
	if (is_equal(cmd[0], "echo") == 1)
		_echo(cmd);
	else if (is_equal(cmd[0], "cd") == 1)
		_cd(cmd);
	else if (is_equal(cmd[0], "pwd") == 1)
		_pwd();
	else if (is_equal(cmd[0], "export") == 1)
		_export(cmd, env);
	else if (is_equal(cmd[0], "unset") == 1)
		_unset(cmd, env);
	else if (is_equal(cmd[0], "env") == 1)
		_env(*env);
	else if (is_equal(cmd[0], "exit") == 1)
		exit(1);
	//if (execve() == -1)
		printf("minishell: command not found: %s\n", cmd[0]);
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
