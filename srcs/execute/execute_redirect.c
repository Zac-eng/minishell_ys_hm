/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:24:22 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/06/16 18:29:39 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redirect_output(t_file *file_head);
static void	redirect_input(t_file *file_head, t_env **env);
static void	read_out_file(int fd);

void	execute_redirect(t_parser *cmd, t_env **env, char **paths)
{
	int		std_in;
	int		std_out;

	if (cmd == NULL || env == NULL || paths == NULL)
		return ;
	if (cmd->file == NULL)
		return (execute_cmd(cmd->cmd, env, paths));
	std_in = dup(0);
	std_out = dup(1);
	if (std_in < 0 || std_out < 0)
		exit(1);
	redirect_input(cmd->file, env);
	redirect_output(cmd->file);
	execute_cmd(cmd->cmd, env, paths);
	if (dup2(std_in, 0) < 0)
		exit(1);
	if (dup2(std_out, 1) < 0)
		exit(1);
}

static void	redirect_output(t_file *file_head)
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
				exit(1);
			if (current->type == APPEND)
				read_out_file(fd);
			if (dup2(fd, 1) < 0)
				exit(1);
		}
		current = current->next;
	}
}

static void	redirect_input(t_file *file_head, t_env **env)
{
	t_file	*current;
	int		fd;

	current = file_head;
	while (current != NULL)
	{
		if (current->type == IN_FILE)
		{
			fd = open(current->file_name, O_RDONLY);
			if (fd < 0)
				exit(1);
			if (dup2(fd, 0) < 0)
				exit(1);
		}
		else if (current->type == HEREDOC)
		{
			fd = heredoc(file_head, env);
			if (fd < 0)
				exit(1);
			if (dup2(fd, 0) < 0)
				exit(1);
		}
		else if (current->type == QUOTE_HEREDOC)
		{
			fd = quote_heredoc(file_head, env);
			if (fd < 0)
				exit(1);
			if (dup2(fd, 0) < 0)
				exit(1);
		}
		current = current->next;
	}
}

static void	read_out_file(int fd)
{
	char	buffer[1024];
	int		read_len;

	read_len = sizeof(buffer);
	while (read_len == sizeof(buffer))
	{
		read_len = read(fd, buffer, sizeof(buffer));
		if (read_len < 0)
			exit(1);
	}
}
