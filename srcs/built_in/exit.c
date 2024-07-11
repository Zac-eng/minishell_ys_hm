/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/16 18:05:59 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/07/11 11:55:51 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_numeric(char *str);

void	minishell_exit(char **cmd)
{
	char	*error_message;

	write(1, "exit\n", 5);
	if (cmd == NULL || cmd[0] == NULL || cmd[1] == NULL)
		exit(0);
	if (cmd[2] != NULL)
	{
		write(2, "minishell: exit: too many arguments\n", 36);
		exit(1);
	}
	if (is_numeric(cmd[1]) == false)
	{
		error_message = join_three_strs(\
			"minishell: exit: ", cmd[1], ": numeric argument required\n");
		write(2, error_message, ft_strlen(error_message));
		free(error_message);
		exit(-1);
	}
	exit(ft_atoi(cmd[1]));
}

static bool	is_numeric(char *str)
{
	if (str == NULL)
		return (false);
	if (*str == '+' || *str == '-')
	{
		str++;
		if (*str < '0' || '9' < *str)
			return (false);
	}
	while (*str != '\0')
	{
		if (*str < '0' || '9' < *str)
			return (false);
		str++;
	}
	return (true);
}
