/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:24:22 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/05/30 15:22:47 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	execute_multiple(t_parser *cmd, t_env **env, char **paths);
static int	redirect_output(char *file_path, t_redirect_type method);
static void	open_files(t_file *file_head, int *fd_list);
static void	close_files(int *fd_list);

void	execute_redirect(t_parser *cmd, t_env **env, char **paths)
{
	t_file	*current_file;
	int		std_out;
	int		fd;

	if (cmd == NULL || env == NULL || paths == NULL)
		return ;
	if (cmd->file == NULL)
		return (execute_cmd(cmd->cmd, env, paths));
	std_out = dup(1);
	if (std_out < 0)
		exit(1);
	current_file = cmd->file;
	while (current_file != NULL)
	{
		if (current_file->type == OUT_FILE || current_file->type == APPEND)
		{
			fd = redirect_output(current_file->file_name, current_file->type);
			execute_multiple(cmd, env, paths);
			close(fd);
		}
		current_file = current_file->next;
	}
	if (dup2(std_out, 1) < 0)
		exit(1);
}

static void	execute_multiple(t_parser *cmd, t_env **env, char **paths)
{
	int		in_fds[OPEN_MAX];
	int		std_in;
	int		index;

	index = 0;
	ft_bzero(in_fds, sizeof(in_fds));
	open_files(cmd->file, &in_fds[0]);
	std_in = dup(0);
	if (std_in < 0)
		exit(1);
	//execute_cmd(cmd->cmd, env, paths);
	while (in_fds[index] != 0)
	{
		if (dup2(in_fds[index], 0) < 0)
			exit(1);
		execute_cmd(cmd->cmd, env, paths);
		index += 1;
	}
	close_files(&in_fds[0]);
	if (dup2(std_in, 0) < 0)
		exit(1);
}

static int	redirect_output(char *file_path, t_redirect_type method)
{
	char	buffer[1024];
	int		fd;
	int		read_len;

	read_len = sizeof(buffer);
	if (method == OUT_FILE)
		unlink(file_path);
	fd = open(file_path, O_CREAT | O_RDWR, 0666);
	if (fd < 0)
		exit(1);
	if (method == APPEND)
	{
		while (read_len == sizeof(buffer))
		{
			read_len = read(fd, buffer, sizeof(buffer));
			if (read_len < 0)
				exit(1);
		}
	}
	if (dup2(fd, 1) < 0)
		exit(1);
	return (fd);
}

static void	open_files(t_file *file_head, int *fd_list)
{
	t_file	*current;
	int		fd;

	if (file_head == NULL)
		return ;
	current = file_head;
	while (current != NULL)
	{
		if (current->type == IN_FILE)
		{
			fd = open(current->file_name, O_RDONLY);
			if (fd < 0)
				exit(1);
			*fd_list = fd;
			fd_list += 1;
		}
		current = current->next;
	}
}

static void	close_files(int *fd_list)
{
	while (*fd_list != 0)
	{
		if (close(*fd_list) != 0)
			exit(1);
		fd_list += 1;
	}
}
