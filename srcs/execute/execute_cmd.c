/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:43:54 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/06/30 18:36:17 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_execve(char **cmd, t_env *env, char **paths);
static void	execute_path(char *path, char **cmd, char **env);

void	execute_cmd(char **cmd, t_env **env, char **paths)
{
	if (cmd == NULL || env == NULL)
		return ;
	if (is_equal(cmd[0], "echo") == 1)
		return (_echo(cmd));
	else if (is_equal(cmd[0], "cd") == 1)
		return (_cd(cmd, *env));
	else if (is_equal(cmd[0], "pwd") == 1)
		return (_pwd());
	else if (is_equal(cmd[0], "export") == 1)
		return (_export(cmd, env));
	else if (is_equal(cmd[0], "unset") == 1)
		return (_unset(cmd, env));
	else if (is_equal(cmd[0], "env") == 1)
		return (_env(*env, false));
	else if (is_equal(cmd[0], "exit") == 1)
		return (minishell_exit(cmd));
	else
		execute_execve(cmd, *env, paths);
}

static void	execute_execve(char **cmd, t_env *env, char **paths)
{
	char	**env_str;

	if (cmd == NULL || cmd[0] == NULL)
		return ;
	env_str = env_into_list(env);
	if (env_str == NULL)
		return ;
	if (ft_strchr(cmd[0], '/') == NULL)
		execute_envpath(paths, cmd, env_str);
	else
		execute_path(cmd[0], cmd, env_str);
	free_str_list(env_str);
}

static void	execute_path(char *path, char **cmd, char **env)
{
	pid_t	pid;

	if (cmd == NULL)
		return ;
	pid = safe_fork();
	if (pid == 0)
	{
		if (execve(path, cmd, env) == -1)
		{
			perror(strerror(errno));
			exit(g_flag);
		}
	}
	handle_status(pid);
}
