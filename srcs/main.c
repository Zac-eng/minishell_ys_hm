/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 10:21:14 by yususato          #+#    #+#             */
/*   Updated: 2024/03/13 08:54:47 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_error_exit(char *error);
void	handle_status(int *status);

int	main(int argc, char **argv, char **env)
{
	char	*line;
	pid_t	pid;
	int		status;

	signalctrl();
	while (true)
	{
		line = readline("> ");
		if (!line)
			break ;
		else
		{
			add_history(line);
			pid = fork();
			if (pid < 0)
				put_error_exit("failed to fork");
			else if (pid == 0)
				exit(0);
			else
				handle_status(&status);
			free(line);
		}
	}
	exit(0);
}

__attribute((destructor)) static void destructor() {
	system("leaks -q minishell");
}

void	put_error_exit(char *error)
{
	perror(error);
	exit(1);
}

void	handle_status(int *status)
{
	wait(status);
	printf("status: %d\n", *status);
	if (*status != 0)
		exit(1);
}

// int	main(int ac, char **av, char **env)
// {
// 	char	*line;
// 	t_stack	stack;
// 	t_stack	sum;
// 	t_node	*node;
// 	pid_t	pid;
// 	int		status;
// 	char	*path;

// 	//using_history();
// 	signal(SIGINT, sig_handler);
// 	while (true)
// 	{
// 		line = readline("> ");
// 		if (!line)
// 			break ;
// 		if (line)
// 		{
// 			add_history(line);
// 			path = get_pass(line);
// 			pid = fork();
// 			if (pid < 0)
// 			{
// 				perror("fork");
// 				exit(0);
// 			}
// 			else if (pid == 0)
// 			{
// 				char *args[] = {line, NULL};
				
// 				if (execve(path, args, env) == -1)
// 				{
// 					perror("execve");
// 					exit(0);
// 				}
// 			}
// 				else
// 					wait(&status);
// 			printf("%d\n",status);
// 			free(line);
			
			
// 			// stack = lexer(line);
// 			// node = stack.top;
// 			// node->next = NULL;
// 			// while (node->prev != NULL)
// 			// 	node = node->prev;
// 			// parser(node);

// 		}
// 	}
// 	exit(0);
// }

// char	*get_pass(char *line)
// {
// 	char	path[PATH_MAX];
// 	char	*str;
// 	char	*end;
// 	char	*copy;

// 	str = getenv("PATH");
// 	while (*str)
// 	{
// 		bzero(path, PATH_MAX);
// 		end = strchr(str, ':');
// 		if (end)
// 			strncpy(path, str, end - str);
// 		else
// 			strlcpy(path, str, end - str);
// 		strlcat(path, "/", PATH_MAX);
// 		strlcat(path, line, PATH_MAX);
// 		if (access(path, X_OK) == 0)
// 		{
// 			copy = strdup(path);
// 			if (copy == NULL)
// 				exit(0);
// 			return (copy);
// 		}
// 		if (end == NULL)
// 			return (NULL);
// 		str = end + 1;
// 	}
// 	return (NULL);
// }

