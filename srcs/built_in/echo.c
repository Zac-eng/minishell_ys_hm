/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 09:55:49 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/07/04 08:04:08 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_echo_n(char **words);

void	_echo(char **cmd)
{
	if (cmd == NULL || cmd[0] == NULL)
	{
		g_flag = 0;
		return ;
	}
	if (cmd[1] != NULL && is_equal(cmd[1], "-n") == 1)
		_echo_n(&cmd[2]);
	else
	{
		_echo_n(&cmd[1]);
		printf("\n");
	}
}

static void	_echo_n(char **words)
{
	int	iter;

	g_flag = 0;
	iter = 0;
	if (words == NULL || words[0] == NULL)
		return ;
	while (words[iter] != NULL && words[iter + 1] != NULL)
	{
		printf("%s ", words[iter]);
		iter++;
	}
	if (words[iter] != NULL)
		printf("%s", words[iter]);
}
