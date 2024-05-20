/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 10:21:14 by yususato          #+#    #+#             */
/*   Updated: 2024/05/13 18:34:30 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_env	*tenv;
	char	*line;
	t_token *lexer_head;
	t_parser *parser_head;

	(void)argc;
	(void)argv;
	signalctrl();
	tenv = env_into_tenv(env);
	while (true)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (line)
		{
			lexer_head = lexer(line);
			parser_head = parser(lexer_head);
			int i =0;
			int a = 0;
			int j = 0;
			while (parser_head->next != NULL)
			{
			parser_head = parser_head->next;
			}
			while (parser_head != NULL)
			{
				printf("parser->pointer:%p\n",parser_head );
				while (parser_head->cmd[i] != NULL)
			{
				printf("cmd:%s\n",parser_head->cmd[i] );
				i++;
			}
			while (parser_head->file != NULL)
			{
				printf("filename:%s\n",parser_head->file->file_name );
				parser_head->file = parser_head->file->next;
			}
			a++;
			i=0;
			parser_head = parser_head->prev;
			}
			add_history(line);
			execute(line, &tenv);
			free(line);
		}
	}
	exit(0);
}
__attribute((destructor)) static void destructor() {
	system("leaks -q minishell");
}

// // __attribute((destructor)) static void destructor() {
// // 	system("leaks -q minishell");
// // }

// void	put_error_exit(const char *error)
// {
// 	perror(error);
// 	exit(1);
// }

// void	handle_status(int *status)
// {
// 	wait(status);
// 	printf("status: %d\n", *status);
// 	if (*status != 0)
// 		exit(1);
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
// 			// (node);

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

