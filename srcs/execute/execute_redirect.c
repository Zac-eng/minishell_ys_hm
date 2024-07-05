/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:24:22 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/07/05 19:28:32 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirect_output(t_file *file_head, char *cmd);
static int	redirect_input(t_file *file_head, t_env **env, char *cmd);
// static int	read_out_file(int fd);

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
	int	std_io[2];
	int	file_io[2];

	if (cmd == NULL || env == NULL)
		return ;
	if (cmd->file == NULL)
		return (execute_cmd(cmd->cmd, env, paths, set_st));
	if (save_io(&std_io[0]) < 0)
		return ;
	heredoc_loop(cmd->file, env);
	if (cmd->cmd == NULL)
		return ;
	file_io[0] = redirect_input(cmd->file, env, cmd->cmd[0]);
	if (file_io[0] < 0)
		return ;
	file_io[1] = redirect_output(cmd->file, cmd->cmd[0]);
	if (file_io[1] < 0)
		return ;
	execute_cmd(cmd->cmd, env, paths, set_st);
	get_back_io(&std_io[0]);
	close(file_io[0]);
	close(file_io[1]);
}

static int	redirect_input(t_file *file_head, t_env **env, char *cmd)
{
	t_file			*current;
	t_redirect_type	type;
	int				fd;

	fd = 0;
	current = file_head;
	while (current != NULL)
	{
		type = current->type;
		if (type == IN_FILE || type == HEREDOC || type == QUOTE_HEREDOC)
		{
			if (fd != 0)
				close(fd);
			fd = open(current->file_name, O_RDONLY);
			if (fd < 0)
				return (perror_set_flag(), -1);
			if (dup2(fd, 0) < 0)
				return (perror_set_flag(), -1);
		}
		current = current->next;
	}
	return (fd);
}

static int	redirect_output(t_file *file_head, char *cmd)
{
	t_file	*current;
	int		fd;

	fd = 0;
	current = file_head;
	while (current != NULL)
	{
		if (fd != 0)
			close(fd);
		if (current->type == OUT_FILE)
		{
			unlink(current->file_name);
			fd = open(current->file_name, O_WRONLY | O_CREAT, 0666);
			if (fd < 0)
				return (perror_set_flag(), -1);
			if (dup2(fd, 1) < 0)
				return (perror_set_flag(), -1);
		}
		if (current->type == APPEND)
		{
			if (fd != 0)
				close(fd);
			fd = open(current->file_name, O_WRONLY | O_APPEND | O_CREAT, 0666);
			if (fd < 0)
				return (perror_set_flag(), -1);
			if (dup2(fd, 1) < 0)
				return (perror_set_flag(), -1);
		}
		current = current->next;
	}
	return (fd);
}

// static int	read_out_file(int fd)
// {
// 	char	buffer[1024];
// 	int		read_len;

// 	read_len = sizeof(buffer);
// 	while (read_len == sizeof(buffer) && read_len >= 0)
// 	{
// 		read_len = read(fd, buffer, sizeof(buffer));
// 		if (read_len < 0)
// 			return (perror_set_flag(), -1);
// 	}
// 	return (0);
// }
