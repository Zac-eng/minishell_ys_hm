/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 12:44:33 by h.miyazaki        #+#    #+#             */
/*   Updated: 2024/07/05 19:40:34 by hmiyazak         ###   ########.fr       */
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
			write(2, "minishell: cd: HOME not set\n", 28);
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
