/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:48:42 by yususato          #+#    #+#             */
/*   Updated: 2024/07/07 14:59:26 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	quote_heredoc(t_file *file)
{
	char	*new_file;

	new_file = create_file();
	quote_read_heredoc(file, new_file);
	filename_change(file, new_file);
	return ;
}

void	quote_read_heredoc(t_file *file, char *new_file)
{
	int		fd;
	char	*line;

	while (true)
	{
		fd = open(new_file, O_WRONLY | O_APPEND, 0644);
		if (fd == -1)
			exit(1);
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strlen(line) && !strcmp(line, file->file_name))
		{
			free_close(line, fd);
			break ;
		}
		write(fd, line, strlen(line));
		write(fd, "\n", 1);
		close(fd);
	}
	return ;
}
