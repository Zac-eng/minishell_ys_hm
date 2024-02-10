/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 10:21:14 by yususato          #+#    #+#             */
/*   Updated: 2024/02/08 19:07:30 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_stack	stack;
	t_stack	sum;
	t_node	*node;
	pid_t	pid;
	int		status;
	char	*path;

	using_history();
	while (true)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (line)
		{
			add_history(line);
			path = getenv("PATH");
			pid = fork();
			if (pid < 0)
			{
				perror("fork");
				exit(0);
			}
			else if (pid == 0)
			{
				char *args[] = {line, NULL};
				
				if (execve(line,args,env) == -1)
				{
					perror("execve");
					exit(0);
				}
			}
				else
					wait(&status);
			printf("%d\n",status);
			free(line);
			
			
			// stack = lexer(line);
			// node = stack.top;
			// node->next = NULL;
			// while (node->prev != NULL)
			// 	node = node->prev;
			// parser(node);

		}
	}
	exit(0);
}

// // __attribute((destructor)) static void destructor() {
// // 	system("leaks -q minishell");
// // }
