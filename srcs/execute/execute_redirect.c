/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:24:22 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/06/20 21:03:00 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redirect_output(t_file *file_head, char *cmd);
static void	redirect_input(t_file *file_head, t_env **env, char *cmd);
static void	read_out_file(int fd);
static int	redirect(t_file *file, t_env **env);

g_signal = SIGINT;

void	signal_handler_heredoc_quit(int signum, siginfo_t *info, void *ucontext)
{
	(void)signum;
	(void)ucontext;
	(void)info;
	rl_on_new_line();
	rl_redisplay();
}

void	signal_handler_heredoc(int signum, siginfo_t *info, void *ucontext)
{
	(void)signum;
	(void)ucontext;
	(void)info;
	close(0);
	g_signal = 1;
}

void signal_heredoc(void)
{
struct sigaction act1;
struct sigaction act2;

sigemptyset(&act1.sa_mask);
act1.sa_sigaction = signal_handler_heredoc;
act1.sa_flags = SA_SIGINFO;
sigaction(SIGINT, &act1, NULL);
sigemptyset(&act2.sa_mask);
act2.sa_sigaction = signal_handler_heredoc_quit;
act2.sa_flags = SA_SIGINFO;
sigaction(SIGQUIT, &act2, NULL);
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
			signal_heredoc();
			heredoc(current, env);
		}
		else if (current->type == QUOTE_HEREDOC)
		{
			signal_heredoc();
			quote_heredoc(current, env);
		}
		current = current->next;
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

	if (file->type == IN_FILE || file->type == HEREDOC
		|| file->type == QUOTE_HEREDOC)
	{
		fd = open(file->file_name, O_RDONLY);
		if (fd < 0)
			return (-1);
		if (dup2(fd, 0) < 0)
			exit(1);
	}
	return (0);
}
