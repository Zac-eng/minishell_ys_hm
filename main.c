/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 10:21:14 by yususato          #+#    #+#             */
/*   Updated: 2024/02/16 18:22:47 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_pass(char	*line)
{
	char	path[PATH_MAX];
	char	*str;
	char	*end;
	char	*copy;

	str = getenv("PATH");
	while (*str)
	{
		bzero(path, PATH_MAX);
		end = strchr(str, ':');
		if (end)
			strncpy(path, str, end - str);
		else
			strlcpy(path, str, PATH_MAX);
		strlcat(path, "/", PATH_MAX);
		strlcat(path, line, PATH_MAX);
		if (access(path, X_OK) == 0)
		{
			copy = strdup(path);
			if (copy == NULL)
				return (NULL);
			return (copy);
		}
		if (end == NULL)
			return (NULL);
		str = end + 1;
	}
	return (NULL);
}

int	token_count(t_token *token)
{
	t_token	*tmp;
	int		i;

	i = 0;
	tmp = token;
	while (tmp != NULL)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**token_list(t_token *token)
{
	int		i;
	char	**args;

	i = 0;
	i = token_count(token);
	args = calloc(i + 1, sizeof(char *));
	if (!args)
		ft_error();
	i = 0;
	while (token->next != NULL)
	{
		args[i] = strdup(token->str);
		i++;
		token = token->next;
	}
	return (args);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	char	**args;
	t_token	*token;
	// t_node	*node;
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
			path = get_pass(line);
			token = lexer(line);
			// node = parser(token);
			expand(token);
			pid = fork();
			if (pid < 0)
			{
				perror("fork");
				exit(0);
			}
			else if (pid == 0)
			{
				args = token_list(token);
				if (!path)
				{
					args++;
					while (*args != '\0')
					{
						printf("%s\n",*args);
						args++;
					}
				}
				else if (execve(path, args, env) == -1)
				{
					perror("execve");
					exit(0);
				}
			}
				else
					wait(&status);
			free(line);
		}
	}
	exit(0);
}

// // __attribute((destructor)) static void destructor() {
// // 	system("leaks -q minishell");
// // }
