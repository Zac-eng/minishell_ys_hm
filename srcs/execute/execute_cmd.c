/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:43:54 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/05/31 16:30:26 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_execve(char **cmd, t_env *env, char **paths);
static int	execute_childp(char *path, char **cmd, char **env);
static char	*create_path(char *where, char *cmd_name);

void	execute_cmd(char **cmd, t_env **env, char **paths)
{
	if (cmd == NULL || env == NULL || paths == NULL)
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
	if (execute_execve(cmd, *env, paths) == 256)
		printf("minishell: command not found: %s\n", cmd[0]);
}

static int	execute_execve(char **cmd, t_env *env, char **paths)
{
	int		index;
	char	**env_str;
	int		status;

	if (cmd == NULL || env == NULL || paths == NULL)
		exit(1);
	index = 0;
	status = 256;
	env_str = env_into_list(env);
	if (env_str == NULL)
		exit(1);
	while (paths[index] != NULL && status != 0)
	{
		status = execute_childp(paths[index], cmd, env_str);
		index++;
	}
	if (status > 0)
		status = execute_path(cmd, env_str);
	free_str_list(env_str);
	return (status);
}

static int	execute_childp(char *path, char **cmd, char **env)
{
	int		pid;
	int		status;
	char	*path_line;

	if (path == NULL || cmd == NULL || env == NULL)
		return (-1);
	path_line = create_path(path, cmd[0]);
	if (path_line == NULL)
		exit(1);
	status = 256;
	pid = fork();
	if (pid < 0)
		exit(1);
	else if (pid == 0)
	{
		signal(SIGINT, sigexit);
		if (execve(path_line, cmd, env) == -1)
			exit(-1);
		exit(0);
	}
	else
		wait(&status);
	free(path_line);
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
