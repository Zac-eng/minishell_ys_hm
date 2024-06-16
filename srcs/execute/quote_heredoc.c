/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:48:42 by yususato          #+#    #+#             */
/*   Updated: 2024/06/16 18:30:09 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
# define HEREDOC_FILE "srcs/execute/tmp/heredoc"

int	quote_heredoc(t_file *file, t_env **env)
{
	int		fd;

	fd = open(HEREDOC_FILE, O_CREAT, 0644);
	close(fd);
	quote_read_heredoc(file, env);
	fd = open(HEREDOC_FILE, O_RDONLY);
	return (fd);
}

void	quote_read_heredoc(t_file *file, t_env **env)
{
	int		fd;
	char	*line;

	while (true)
	{
		fd = open(HEREDOC_FILE, O_WRONLY | O_APPEND, 0644);
		if (fd == -1)
			exit(1);
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strlen(line) == 0 && ft_strlen(file->file_name))
		{
			// free_close(line, fd);
			break ;
		}
		else if (ft_strlen(line) && !strcmp(line, file->file_name))
		{
			// free_close(line, fd);
			break ;
		}
		write(fd, line, strlen(line));
		write(fd, "\n", 1);
		close(fd);
	}
	return ;
}
