/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 19:48:42 by yususato          #+#    #+#             */
/*   Updated: 2024/07/09 20:35:38 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	quote_heredoc(t_file *file)
{
	char	*new_file;

	new_file = create_file();
	if (new_file == NULL)
		return (false);
	if (quote_read_heredoc(file, new_file) == false)
		return (false);
	if (filename_change(file, new_file) == false)
		return (false);
	return (true);
}

bool	quote_read_heredoc(t_file *file, char *new_file)
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
		if (ft_strlen(line) && is_equal(line, file->file_name))
		{
			free_close(line, fd);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
		close(fd);
	}
	return (true);
}
