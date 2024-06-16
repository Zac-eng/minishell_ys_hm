/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 12:44:33 by h.miyazaki        #+#    #+#             */
/*   Updated: 2024/06/16 22:11:47 by hmiyazak         ###   ########.fr       */
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
			printf("minishell: cd: HOME not set\n");
			g_status = RUN_ERROR;
			return ;
		}
		destination = home;
	}
	if (chdir(destination) != 0)
	{
		printf("minishell: cd: no such file or directory: %s\n", destination);
		g_status = RUN_ERROR;
	}
	free(home);
}
