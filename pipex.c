/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:17:19 by yususato          #+#    #+#             */
/*   Updated: 2024/01/29 15:22:00 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/minishell.h"

int main(int ac, char **av)
{
	int fd1;
	int fd2;
	int byte1;
	int byte2;
	char str1[1024];
	char str2[1024];
	int pipefd[2];

	if (ac != 5)
		exit(0);
	fd1 = open(av[1], O_RDONLY);
	fd2 = open(av[3], O_RDONLY);
	byte1 = read(fd1, str1, sizeof(str1));
	byte2 = read(fd2, str2, sizeof(str2));

	str1[byte1] = '\0';
	str2[byte2] = '\0';
	if (strstr(str1, av[2]) == NULL)
		return (0);
	if (strstr(str2, av[4]) == NULL)
		return (0);
	pipe();
	return (0);
}

void	pipe(void)
{
    pid_t    pid;
	int pipefd[2];
    extern char    **environ;
    char    *cmd1[3];
    char    *cmd2[3];

    cmd1[0] = strdup("ls");
    cmd1[1] = strdup("-l");
    cmd1[2] = NULL;

    cmd2[0] = strdup("wc");
    cmd2[1] = strdup("-l");
    cmd2[2] = NULL;

    pipe(pipefd);
    pid = fork();
    if (pid == 0)
    {
        dup2(pipefd[1], 1);
        close(pipefd[1]);
        close(pipefd[0]);
        execve("/bin/ls", cmd1, environ);
    }
    dup2(pipefd[0], 0);
    close(pipefd[0]);
    close(pipefd[1]);
    execve("/usr/bin/wc", cmd2, environ);
    return (0);
}