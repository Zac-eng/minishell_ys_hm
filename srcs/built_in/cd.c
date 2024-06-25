/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 12:44:33 by h.miyazaki        #+#    #+#             */
/*   Updated: 2024/06/25 10:57:18 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_cd(char **cmd, t_env *env)
{
	char	*destination;
	char	*home;

	if (cmd == NULL || cmd[0] == NULL)
		return ;
	destination = cmd[1];
	home = _getenv(env, "HOME");
	if (destination == NULL)
	{
		if (home == NULL)
		{
			perror_set_flag();
			return ;
		}
		destination = home;
	}
	if (chdir(destination) != 0)
		perror_set_flag();
	else
		g_flag = 0;
	if (home != NULL)
		free(home);
}
