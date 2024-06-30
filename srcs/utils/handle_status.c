/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_status.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 20:19:08 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/06/30 18:35:25 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_status(pid_t pid_to_wait)
{
	int	status;

	waitpid(pid_to_wait, &status, 0);
	if (status % 256 == 0)
		g_flag = status / 256;
	else
	{
		g_flag = 128 + status;
		printf("\n");
	}
}
