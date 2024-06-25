/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_fork.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/18 08:52:45 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/06/25 09:58:59 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	safe_fork(void)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror(strerror(errno));
		exit(errno);
	}
	return (pid);
}
