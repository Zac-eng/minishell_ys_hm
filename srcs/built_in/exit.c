/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 18:05:59 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/06/16 19:12:11 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_numeric(char *str);

void	minishell_exit(char **cmd)
{
	printf("exit\n");
	if (cmd == NULL || cmd[0] == NULL || cmd[1] == NULL)
		exit(0);
	if (is_numeric(cmd[1]) == false)
	{
		printf("minishell: exit: %s: numeric argument required\n", cmd[1]);
		exit(-1);
	}
	exit(ft_atoi(cmd[1]));
}

static bool	is_numeric(char *str)
{
	if (str == NULL)
		return (false);
	if (*str == '+' || *str == '-')
		str++;
	while (*str != '\0')
	{
		if (*str < '0' || '9' < *str)
			return (false);
		str++;
	}
	return (true);
}
