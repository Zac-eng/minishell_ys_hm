/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_envpath.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 17:24:58 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/07/10 16:05:11 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_path(char *where, char *cmd_name);

void	execute_envpath(char **paths, char **cmd, char **env, bool set_st)
{
	int		pid;
	int		index;
	int		status;

	if (cmd == NULL || cmd[0] == NULL || paths == NULL)
		return ;
	index = 0;
	status = -1;
	pid = safe_fork();
	if (pid == 0)
	{
		while (paths[index] != NULL && status == -1)
		{
			status = execve(create_path(paths[index], cmd[0]), cmd, env);
			index++;
		}
		put_error(NOT_FOUND_ERROR, cmd[0]);
		exit(g_flag);
	}
	handle_status(pid, set_st);
}

static char	*create_path(char *where, char *cmd_name)
{
	char	*path_tmp;
	char	*path;

	path_tmp = ft_strjoin(where, "/");
	if (path_tmp == NULL)
		return (NULL);
	path = ft_strjoin(path_tmp, cmd_name);
	free(path_tmp);
	return (path);
}
