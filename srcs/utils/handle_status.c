/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 20:19:08 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/07/05 16:57:01 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_status(pid_t pid_to_wait, bool set_st)
{
	int	status;

	waitpid(pid_to_wait, &status, 0);
	if (set_st)
	{
		if (WIFEXITED(status))
			g_flag = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			g_flag = 128 + WTERMSIG(status);
		else
			g_flag = 1;
	}
}
