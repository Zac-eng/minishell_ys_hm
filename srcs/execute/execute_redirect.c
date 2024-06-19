/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:24:22 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/06/19 23:29:08 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redirect_output(t_file *file_head, char *cmd);
static void	redirect_input(t_file *file_head, t_env **env, char *cmd);
static void	read_out_file(int fd);
static int	redirect(t_file *file, t_env **env);

char	*create_file(void)
{
	int		i;
	int		fd;
	char	*new;
	char	*tmp;

	fd = 0;
	i = 0;
	tmp = ft_itoa(i);
	new = ft_strjoin(HEREDOC_FILE, tmp);
	if (new == NULL)
		exit(1);
	free(tmp);
	if (new == NULL)
		exit(1);
	while (!access(new, F_OK))
	{
		i++;
		free(new);
		tmp = ft_itoa(i);
		if (tmp == NULL)
			exit(1);
		new = ft_strjoin(HEREDOC_FILE, tmp);
		if (new == NULL)
			exit(1);
		free(tmp);
	}
	fd = open(new, O_CREAT, 0644);
	close(fd);
	return (new);
}

int	heredoc_open(t_file *file, t_env **env)
{
	int	fd;

	fd = heredoc_file_open()
}

void	heredoc_loop(t_file *file, t_env **env)
{
	int		fd;
	t_file	*current;

	current = file;
	while (current != NULL)
	{
		if (current->type == HEREDOC)
		{
			fd = heredoc(current, env);
			if (fd < 0)
				return (-1);
		}
		else if (current->type == QUOTE_HEREDOC)
		{
			fd = quote_heredoc(current, env);
			if (fd < 0)
				return (-1);
		}
	}
}

void	execute_redirect(t_parser *cmd, t_env **env, char **paths)
{
	int		std_in;
	int		std_out;

	if (cmd == NULL || env == NULL)
		return ;
	if (cmd->file == NULL)
		return (execute_cmd(cmd->cmd, env, paths));
	std_in = dup(0);
	std_out = dup(1);
	if (std_in < 0 || std_out < 0)
		return (put_error(FILE_ERROR, cmd->cmd[0]));
	heredoc_loop(cmd->file, env);
	redirect_input(cmd->file, env, cmd->cmd[0]);
	redirect_output(cmd->file, cmd->cmd[0]);
	execute_cmd(cmd->cmd, env, paths);
	if (dup2(std_in, 0) < 0)
		return (exit(1));
	if (dup2(std_out, 1) < 0)
		return (exit(1));
}

static void	redirect_output(t_file *file_head, char *cmd)
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
				return (put_error(FILE_ERROR, cmd));
			if (current->type == APPEND)
				read_out_file(fd);
			if (dup2(fd, 1) < 0)
				return (exit(1));
		}
		current = current->next;
	}
}

static void	redirect_input(t_file *file_head, t_env **env, char *cmd)
{
	t_file	*current;
	int		fd;

	current = file_head;
	while (current != NULL)
	{
		if (redirect(current, env) < 0)
			return (put_error(FILE_ERROR, cmd));
		current = current->next;
	}
}

static void	read_out_file(int fd)
{
	char	buffer[1024];
	int		read_len;

	read_len = sizeof(buffer);
	while (read_len == sizeof(buffer) && read_len >= 0)
	{
		read_len = read(fd, buffer, sizeof(buffer));
		if (read_len < 0)
			return ;
	}
}

static int	redirect(t_file *file, t_env **env)
{
	int	fd;

	if (file->type == IN_FILE)
	{
		fd = open(file->file_name, O_RDONLY);
		if (fd < 0)
			return (-1);
		if (dup2(fd, 0) < 0)
			exit(1);
	}
	else if (file->type == HEREDOC)
	{
		fd = heredoc_open(file, env);
		if (fd < 0)
			return (-1);
		if (dup2(fd, 0) < 0)
			exit(1);
	}
	else if (file->type == QUOTE_HEREDOC)
	{
		fd = quote_heredoc_open(file, env);
		if (fd < 0)
			return (-1);
		if (dup2(fd, 0) < 0)
			exit(1);
	}
	return (0);
}
