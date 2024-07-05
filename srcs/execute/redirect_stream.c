/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_stream.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 22:08:32 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/07/05 23:01:46 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	redirect_input(char *filename, t_redirect_type type, int *infd);
static int	redirect_output(char *filename, t_redirect_type type, int *outfd);

int	redirect_stream(t_file *file_head, int *file_io)
{
	t_file			*current;
	t_redirect_type	type;

	current = file_head;
	while (current != NULL)
	{
		type = current->type;
		if (type == IN_FILE || type == HEREDOC || type == QUOTE_HEREDOC)
		{
			if (redirect_input(current->file_name, type, &file_io[0]) < 0)
				return (-1);
		}
		else if (type == OUT_FILE || type == APPEND)
		{
			if (redirect_output(current->file_name, type, &file_io[1]) < 0)
				return (-1);
		}
		current = current->next;
	}
	return (0);
}

static int	redirect_input(char *filename, t_redirect_type type, int *infd)
{
	if (type == IN_FILE || type == HEREDOC || type == QUOTE_HEREDOC)
	{
		if (*infd != 0)
			close(*infd);
		*infd = open(filename, O_RDONLY);
		if (*infd < 0)
			return (perror_set_flag(), -1);
		if (dup2(*infd, 0) < 0)
			return (perror_set_flag(), -1);
	}
	return (0);
}

static int	redirect_output(char *filename, t_redirect_type type, int *outfd)
{
	if (*outfd != 1)
		close(*outfd);
	if (type == OUT_FILE)
	{
		*outfd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (*outfd < 0)
			return (perror_set_flag(), -1);
		if (dup2(*outfd, 1) < 0)
			return (perror_set_flag(), -1);
	}
	if (type == APPEND)
	{
		*outfd = open(filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
		if (*outfd < 0)
			return (perror_set_flag(), -1);
		if (dup2(*outfd, 1) < 0)
			return (perror_set_flag(), -1);
	}
	return (*outfd);
}

// static int	get_mode(char *filename, mode_t	*mode)
// {
// 	struct stat	file_status;

// 	if (stat(filename, &file_status) < 0)
// 		return (-1);
// 	*mode = file_status.st_mode;
// 	printf("mode: %d\n", *mode);
// 	return (0);
// }
