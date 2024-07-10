/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 17:43:54 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/07/10 14:39:51 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_execve(char **cmd, t_env *env, char **paths, bool set_st);
static void	execute_path(char *path, char **cmd, char **env, bool set_st);

void	execute_cmd(char **cmd, t_env **env, char **paths, bool set_st)
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
		execute_execve(cmd, *env, paths, set_st);
}

static void	execute_execve(char **cmd, t_env *env, char **paths, bool set_st)
{
	char	**env_str;

	if (cmd == NULL || cmd[0] == NULL)
		return ;
	env_str = env_into_list(env);
	if (env_str == NULL)
		return ;
	if (paths != NULL && ft_strchr(cmd[0], '/') == NULL)
		execute_envpath(paths, cmd, env_str, set_st);
	else
		execute_path(cmd[0], cmd, env_str, set_st);
	free_str_list(env_str);
}

static void	execute_path(char *path, char **cmd, char **env, bool set_st)
{
	pid_t	pid;

	if (cmd == NULL)
		return ;
	pid = safe_fork();
	if (pid == 0)
	{
		if (execve(path, cmd, env) == -1)
		{
			write(2, "minishell: ", 11);
			perror(cmd[0]);
			if (errno == EACCES)
				exit(126);
			else if (errno == EISDIR)
				exit(126);
			else if (errno == ENOENT)
				exit(127);
			else
				exit(EXIT_FAILURE);
		}
	}
	handle_status(pid, set_st);
}
