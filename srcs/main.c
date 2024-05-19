/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 10:21:14 by yususato          #+#    #+#             */
/*   Updated: 2024/05/16 18:54:38 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_env	*tenv;
	char	*line;

	(void)argc;
	(void)argv;
	signalctrl();
	tenv = env_into_tenv(env);
	while (true)
	{
		line = readline("> ");
		if (!line)
			break ;
		else
		{
			add_history(line);
			execute(line, &tenv);
			free(line);
		}
	}
	free_env(tenv);
	rl_clear_history();
	exit(0);
}
// __attribute((destructor)) static void destructor() {
// 	system("leaks -q minishell");
// }





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

