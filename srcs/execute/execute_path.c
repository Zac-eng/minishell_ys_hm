/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 15:51:55 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/05/31 16:26:18 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*extract_command(char *cmd);
static int	copy_command(char *dest, char *ref, int len);
static int	get_command_len(char *cmd);

int	execute_path(char **cmd, char **env)
{
	char	*path;
	char	*command;
	int		pid;
	int		status;

	if (cmd == NULL || env == NULL)
		return (-1);
	path = cmd[0];
	status = 0;
	command = extract_command(cmd[0]);
	if (command == NULL)
		return (-1);
	cmd[0] = command;
	pid = fork();
	if (pid < 0)
		return (-1);
	else if (pid == 0)
	{
		if (execve(path, cmd, env) != 0)
			exit(1);
	}
	else
		wait(&status);
	cmd[0] = path;
	free(command);
	return (status);
}

static char	*extract_command(char *cmd)
{
	char	*command;
	int		len;

	if (cmd == NULL)
		return (NULL);
	len = get_command_len(cmd);
	if (len < 0)
		return (NULL);
	command = (char *)malloc(sizeof(char) * (len + 1));
	if (command == NULL)
		return (NULL);
	if (copy_command(command, cmd, len) != 0)
	{
		free(command);
		return (NULL);
	}
	return (command);
}

static int	copy_command(char *dest, char *ref, int len)
{
	int	dest_index;
	int	ref_index;

	dest_index = 0;
	ref_index = 0;
	while (ref[ref_index] != '/')
		ref_index++;
	ref_index += 1;
	while (ref_index != '\0' && dest_index < len)
	{
		dest[dest_index] = ref[ref_index];
		dest_index++;
		ref_index++;
	}
	dest[dest_index] = '\0';
	if (dest_index != len)
		return (-1);
	return (0);
}

static int	get_command_len(char *cmd)
{
	int		index;
	int		len;

	if (cmd == NULL)
		return (-1);
	index = 0;
	len = 0;
	while (cmd[index] != '\0')
		index++;
	while (cmd[index - len] != '/')
		len++;
	return (len);
}
