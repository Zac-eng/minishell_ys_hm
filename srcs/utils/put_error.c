/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 20:18:16 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/07/10 22:10:21 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_error_efd(t_code error_code, char *insert);

void	perror_set_flag(char *insert)
{
	perror(insert);
	g_flag = 1;
}

void	put_error(t_code error_code, char *insert)
{
	if (error_code == EXPORT_ERROR || error_code == UNSET_ERROR)
	{
		write_error_efd(error_code, insert);
		g_flag = 1;
	}
	else if (error_code == NOT_FOUND_ERROR)
	{
		write_error_efd(error_code, insert);
		g_flag = 127;
	}
	else if (error_code == PARSE_ERROR)
	{
		write_error_efd(error_code, insert);
		g_flag = 258;
	}
}

void	put_error_exit(t_code error_code)
{
	if (error_code == FORK_ERROR)
		write(2, "fork failed: resource temporarily unavailable\n", 46);
	exit(149);
}

static void	write_error_efd(t_code error_code, char *insert)
{
	if (error_code == EXPORT_ERROR)
	{
		write(2, "minishell: export: `", 20);
		write(2, insert, ft_strlen(insert));
		write(2, "': not a valid identifier\n", 26);
	}
	else if (error_code == UNSET_ERROR)
	{
		write(2, "minishell: unset: `", 19);
		write(2, insert, ft_strlen(insert));
		write(2, "': not a valid identifier\n", 26);
	}
	else if (error_code == NOT_FOUND_ERROR)
	{
		write(2, "minishell: ", 12);
		write(2, insert, ft_strlen(insert));
		write(2, ": command not found\n", 20);
	}
	else if (error_code == PARSE_ERROR)
	{
		write(2, "minishell: syntax error near unexpected token `", 47);
		write(2, insert, ft_strlen(insert));
		write(2, "'\n", 2);
	}
}
