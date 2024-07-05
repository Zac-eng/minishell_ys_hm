/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:24:22 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/07/05 16:55:26 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirect_output(t_file *file_head, char *cmd);
static int	redirect_input(t_file *file_head, t_env **env, char *cmd);
static int	read_out_file(int fd);
static int	redirect(t_file *file, t_env **env);

void	heredoc_loop(t_file *file, t_env **env)
{
	int		fd;
	t_file	*current;

	current = file;
	while (current != NULL)
	{
		if (current->type == HEREDOC)
		{
			heredoc(current, env);
		}
		else if (current->type == QUOTE_HEREDOC)
		{
			quote_heredoc(current, env);
		}
		current = current->next;
	}
}

void	execute_redirect(t_parser *cmd, t_env **env, char **paths, bool set_st)
{
	int		std_in;
	int		std_out;

	if (cmd == NULL || env == NULL)
		return ;
	if (cmd->file == NULL)
		return (execute_cmd(cmd->cmd, env, paths, set_st));
	std_in = dup(0);
	std_out = dup(1);
	if (std_in < 0 || std_out < 0)
		return (perror_set_flag());
	heredoc_loop(cmd->file, env);
	if (cmd->cmd == NULL)
		return ;
	if (redirect_input(cmd->file, env, cmd->cmd[0]) < 0)
		return ;
	if (redirect_output(cmd->file, cmd->cmd[0]) < 0)
		return ;
	execute_cmd(cmd->cmd, env, paths, set_st);
	if (dup2(std_in, 0) < 0)
		return (perror_set_flag());
	if (dup2(std_out, 1) < 0)
		return (perror_set_flag());
}

static int	redirect_output(t_file *file_head, char *cmd)
{
	t_file	*current;
	int		fd;

	current = file_head;
	while (current != NULL)
	{
		if (current->type == OUT_FILE || current->type == APPEND)
		{
			if (current->type == OUT_FILE)
				unlink(current->file_name);
			fd = open(current->file_name, O_CREAT | O_RDWR, 0666);
			if (fd < 0)
				return (perror_set_flag(), -1);
			if (current->type == APPEND)
			{
				if (read_out_file(fd) < 0)
					return (-1);
			}
			if (dup2(fd, 1) < 0)
				return (perror_set_flag(), -1);
			close(fd);
		}
		current = current->next;
	}
	return (0);
}

static int	redirect_input(t_file *file_head, t_env **env, char *cmd)
{
	t_file	*current;
	int		fd;

	current = file_head;
	while (current != NULL)
	{
		if (redirect(current, env) < 0)
			return (-1);
		current = current->next;
	}
	return (0);
}

static int	read_out_file(int fd)
{
	char	buffer[1024];
	int		read_len;

	read_len = sizeof(buffer);
	while (read_len == sizeof(buffer) && read_len >= 0)
	{
		read_len = read(fd, buffer, sizeof(buffer));
		if (read_len < 0)
			return (perror_set_flag(), -1);
	}
	return (0);
}

static int	redirect(t_file *file, t_env **env)
{
	int	fd;

	if (file->type == IN_FILE || file->type == HEREDOC
		|| file->type == QUOTE_HEREDOC)
	{
		fd = open(file->file_name, O_RDONLY);
		if (fd < 0)
			return (perror_set_flag(), -1);
		if (dup2(fd, 0) < 0)
			return (perror_set_flag(), -1);
		close(fd);
	}
	return (0);
}
