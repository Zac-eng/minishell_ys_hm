/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 19:28:09 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/04/29 12:04:06 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define READ  (0)
#define WRITE (1)

static void	execute_cmd(char **cmd, char **env);
static int	is_equal(char *str, char *ref);
static void	sigexit(int signum);

void	execute(char *line, char **env)
{
	int		pid;
	int		status;
	int		pipes[2];
	char	buf[1024];

	(void)env;
	pid = fork();
	printf("line %s\n", line);
	char	*cmd[2] = {line, "libft"};
	if (pid < 0)
		exit(0);
	else if (pid == 0)
	{
		printf("child\n");
		signal(SIGINT, sigexit);
		execute_cmd(&cmd[0], env);
		exit(0);
	}
	else
	{
		wait(&status);
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

static void	execute_cmd(char **cmd, char **env)
{
	if (is_equal(cmd[0], "echo") == 1)
		_echo(0, cmd);
	else if (is_equal(cmd[0], "cd") == 1)
		_cd(cmd[1]);
	else if (is_equal(cmd[0], "pwd") == 1)
		_pwd();
	else if (is_equal(cmd[0], "export") == 1)
		_export("TEST", "test");
	else if (is_equal(cmd[0], "unset") == 1)
		_unset("TEST");
	else if (is_equal(cmd[0], "env") == 1)
		_env(env);
	else if (is_equal(cmd[0], "exit") == 1)
		exit(1);
	else
	{
		printf("minishell: command not found: %s\n", cmd[0]);
		exit(0);
	}
}

static int	is_equal(char *str, char *ref)
{
	int	iter;

	iter = 0;
	if (str == NULL || ref == NULL)
		return (-1);
	while (str[iter] && ref[iter])
	{
		if (str[iter] != ref[iter])
			return (0);
		iter++;
	}
	if (str[iter] == '\0' && ref[iter] == '\0')
		return (1);
	else
		return (0);
}

static void	sigexit(int signum)
{
	(void)signum;
	exit(0);
}
