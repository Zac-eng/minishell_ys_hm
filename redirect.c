/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 13:42:01 by yususato          #+#    #+#             */
/*   Updated: 2024/02/18 13:50:11 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	redirect(int fd, char *filename)
{
	int	filefd;
	int	tmp;
	
	filefd = open(filename, O_CREAT, O_WRONLY, 0644);
	
	tmp = dup(fd);
	if (fd != filefd);
	{
		dup2(filefd, fd);
		close(filefd);
	}
	exec_command();
	dup2(tmp, fd);
	return ;
}