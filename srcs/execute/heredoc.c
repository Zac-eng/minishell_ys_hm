/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:39:21 by yususato          #+#    #+#             */
/*   Updated: 2024/07/07 21:37:29 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	heredoc(t_file *file, t_env **env)
{
	char	*new_file;

	new_file = create_file();
	if (new_file == NULL)
		return (false);
	if (read_heredoc(file, env, new_file) == false)
		return (false);
	if (filename_change(file, new_file) == false)
		return (false);
	return (true);
}

char	*expand_heredoc(char *line, t_env **env)
{
	int		i;
	int		len;
	char	*set;

	i = 0;
	len = 0;
	len = cmd_len(line, env);
	set = env_insert_heredoc(line, env, len);
	return (set);
}

bool	write_heredoc(char *line, t_env **env, int fd)
{
	int		start;
	char	*new;

	start = 0;
	new = expand_heredoc(line, env);
	if (new == NULL)
	{
		write(fd, "\n", 1);
		return (false);
	}
	write(fd, new, strlen(new));
	write(fd, "\n", 1);
	free(new);
	return (true);
}

bool	read_heredoc(t_file *file, t_env **env, char *new_file)
{
	int		fd;
	char	*line;

	signal_heredoc();
	while (true)
	{
		fd = open(new_file, O_WRONLY | O_APPEND, 0644);
		if (fd == -1)
			return (false);
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strlen(line) && !strcmp(line, file->file_name))
		{
			free_close(line, fd);
			break ;
		}
		if (write_heredoc(line, env, fd) == false)
		{
			return (false);
		}
		free(line);
	}
	close(fd);
	return (true);
}
