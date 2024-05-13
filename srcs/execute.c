/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 19:28:09 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/05/13 21:43:45 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser.h"
#define READ  (0)
#define WRITE (1)

static void	execute_redirect(t_parser *cmd, t_env **env);
static void	execute_pipe(t_parser *cmd, t_env **env);
static void	execute_cmd(char **cmd, t_env **env);
static void	sigexit(int signum);

void	execute(char *line, t_env **env)
{
	t_parser	*current;

	if (line == NULL || env == NULL)
		exit(1);

	//instead of using parser, from here
	t_parser	parser1;
	t_parser	parser2;
	t_file		file1;
	char *cmd1[] = {"echo", "-n", "thisi", NULL};
	char *cmd2[] = {"pwd", NULL};
	parser1.cmd = &cmd1[0];
	parser1.file = NULL;
	parser1.next = &parser2;
	parser1.prev = NULL;
	parser2.cmd = &cmd2[0];
	parser2.file = &file1;
	parser2.next = NULL;
	parser2.prev = &parser1;
	file1.file_name = "./test";
	file1.type = OUT_FILE;
	file1.next = NULL;
	//to here

	current = &parser1;
	// signal(SIGINT, sigexit);
	while (current != NULL)
	{
		if (current->next != NULL)
			execute_pipe(current, env);
		else if (current->file != NULL)
			execute_redirect(current, env);
		else
			execute_cmd(current->cmd, env);
		current = current->next;
	}
	// exit(0);
}

static void	execute_pipe(t_parser *cmd, t_env **env)
{
	int		pipes[2];
	int		pid;
	int		original_stdin;
	int		status;
	char	buffer[6];

	if (cmd == NULL || env == NULL)
		return ;
	if (cmd->next == NULL)
		return (execute_redirect(cmd, env));
	if (pipe(pipes) != 0)
		exit(1);
	pid = fork();
	if (pid < 0)
		put_error_exit("failed to fork");
	else if (pid == 0)
	{
		dup2(pipes[WRITE], 1);
		execute_redirect(cmd, env);
		exit(0);
	}
	else
	{
		original_stdin = dup(0);
		dup2(pipes[READ], 0);
		read(0, buffer, 5);
		buffer[5] = '\0';
		printf("parent': %s\n", buffer);
		wait(&status);
		dup2(original_stdin, 0);
	}
}

static void	execute_redirect(t_parser *cmd, t_env **env)
{
	int	pid;
	int	status;
	int	fd;

	if (cmd == NULL || env == NULL)
		return ;
	if (cmd->file == NULL)
		return (execute_cmd(cmd->cmd, env));
	pid = fork();
	if (pid < 0)
		return ;
	else if (pid == 0)
	{
		fd = open(cmd->file->file_name, O_RDWR);
		printf("fd%d\n", fd);
		if (fd < 0)
			exit(1);
		dup2(fd, 1);
		execute_cmd(cmd->cmd, env);
		close(fd);
		exit(0);
	}
	else
		handle_status(&status);
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
	signal(SIGINT, sigexit);
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
	else
		printf("minishell: command not found: %s\n", cmd[0]);
}

static void	sigexit(int signum)
{
	(void)signum;
	exit(0);
}
