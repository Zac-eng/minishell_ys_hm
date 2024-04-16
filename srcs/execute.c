/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 19:28:09 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/03/13 12:06:08 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#define READ  (0)
#define WRITE (1)

void	execute(char **cmd, t_token sign)
{
	int		pid;
	int		status;
	int		pipes[2];
	char	buf[1024];

	if (cmd == NULL || *cmd == NULL)
		return ;
	if (pipe(pipes) < 0)
		return ;
	pid = fork();
	if (pid < 0)
		exit(1);
	else if (pid == 0)
	{
		dup2(pipes[WRITE], 1);
		printf("called");
	}
	else
	{
		dup2(pipes[READ], 0);
		read(0, buf, 4);
		printf("%d, %s\n", getpid(), buf);
	}
}

void	pipes_exec(char **cmd)
{
	
}

// int	main(void)
// {
// 	char *cmd[] = {"ls", "-a"};

// 	execute(&cmd[0], PIPE);
// 	return (0);
// }

static void	execute_cmd(char **cmd)
{
	if (is_equal(cmd[0], "echo") == 1)
		echo(cmd);
	else if (is_equal(cmd[0], "cd") == 1)
		cd(cmd);
	else if (is_equal(cmd[0], "pwd") == 1)
		pwd(cmd);
	else if (is_equal(cmd[0], "export") == 1)
		export(cmd);
	else if (is_equal(cmd[0], "unset") == 1)
		unset(cmd);
	else if (is_equal(cmd[0], "env") == 1)
		env(cmd);
	else if (is_equal(cmd[0], "exit") == 1)
		exit(1);
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
