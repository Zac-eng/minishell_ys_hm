/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 12:44:33 by h.miyazaki        #+#    #+#             */
/*   Updated: 2024/06/25 10:28:31 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_cd(char **cmd, t_env *env)
{
	char	*destination;
	char	*home;

	if (cmd == NULL || cmd[0] == NULL)
		return ;
	home = _getenv(env, "HOME");
	destination = cmd[1];
	if (destination == NULL)
	{
		if (home == NULL)
		{
			perror("");
			g_flag = RUN_ERROR;
			return ;
		}
		destination = home;
	}
	if (chdir(destination) != 0)
	{
		perror("");
		g_flag = RUN_ERROR;
	}
	else
		g_flag = 0;
	free(home);
}
