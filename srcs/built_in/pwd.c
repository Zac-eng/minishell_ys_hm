/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:16:38 by yususato          #+#    #+#             */
/*   Updated: 2024/06/16 18:03:41 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_pwd(char **cmd)
{
	char	path[PATH_MAX];

	if (cmd == NULL)
		return ;
	else if (cmd[1] != NULL)
	{
		printf("pwd: too many arguments\n");
		g_status = RUN_ERROR;
		return ;
	}
	if (getcwd(path, sizeof(path)) != NULL)
		printf("%s\n", path);
	else
	{
		printf("pwd: getcwd failed\n");
		g_status = RUN_ERROR;
	}
	return ;
}
