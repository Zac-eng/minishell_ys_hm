/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_envpath.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 17:24:58 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/07/05 16:57:09 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_path(char *where, char *cmd_name);

void	execute_envpath(char **paths, char **cmd, char **env, bool set_st)
{
	int		pid;
	int		index;
	int		status;

	if (cmd == NULL || cmd[0] == NULL)
		return ;
	if (paths == NULL)
		return (perror_set_flag());
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
		write(2, "minishell: command not found\n", 29);
		exit(NOT_FOUND_ERROR);
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
