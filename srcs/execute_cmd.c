/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:43:54 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/05/23 20:06:12 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_execve(char **cmd, t_env *env, char **paths);
static char	*create_path(char *where, char *cmd_name);

void	execute_cmd(char **cmd, t_env **env, char **paths)
{
	if (cmd == NULL || env == NULL)
		return ;
	if (is_equal(cmd[0], "echo") == 1)
		return (_echo(cmd));
	else if (is_equal(cmd[0], "cd") == 1)
		return (_cd(cmd));
	else if (is_equal(cmd[0], "pwd") == 1)
		return (_pwd());
	else if (is_equal(cmd[0], "export") == 1)
		return (_export(cmd, env));
	else if (is_equal(cmd[0], "unset") == 1)
		return (_unset(cmd, env));
	else if (is_equal(cmd[0], "env") == 1)
		return (_env(*env));
	else if (is_equal(cmd[0], "exit") == 1)
		return (exit(1));
	if (execute_execve(cmd, *env, paths) != 0)
		printf("minishell: command not found: %s\n", cmd[0]);
}

static int	execute_execve(char **cmd, t_env *env, char **paths)
{
	int		index;
	char	**env_str;
	int		pid;
	int		status;

	index = 0;
	status = 256;
	env_str = env_into_list(env);
	if (env_str == NULL)
		return (-1);
	while (paths[index] != NULL && status == 256)
	{
		pid = fork();
		if (pid < 0)
			break ;
		else if (pid == 0)
		{
			if (execve(create_path(paths[index], cmd[0]), cmd, env_str) == -1)
				exit(1);
		}
		else
			wait(&status);
		index++;
	}
	return (status);
}

static char	*create_path(char *where, char *cmd_name)
{
	char	*path_tmp;
	char	*path;

	path_tmp = ft_strjoin(where, "/");
	if (path_tmp == NULL)
		exit(1);
	path = ft_strjoin(path_tmp, cmd_name);
	free(path_tmp);
	if (path == NULL)
		exit(1);
	return (path);
}
