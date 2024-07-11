/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 20:18:16 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/07/11 11:08:49 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	write_error_efd(t_code error_code, char *insert);
static char	*join_three_strs(char *s1, char *s2, char *s3);

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
	char	*error_message;

	error_message = NULL;
	if (error_code == EXPORT_ERROR)
		error_message = join_three_strs("minishell: export: `", insert, \
										"': not a valid identifier\n");
	else if (error_code == UNSET_ERROR)
		error_message = join_three_strs("minishell: unset: `", insert, \
										"': not a valid identifier\n");
	else if (error_code == NOT_FOUND_ERROR)
		error_message = join_three_strs("minishell: ", insert, \
									": command not found\n");
	else if (error_code == PARSE_ERROR)
		error_message = join_three_strs(\
		"minishell: syntax error near unexpected token `", insert, "'\n");
	else
		return ;
	write(2, error_message, ft_strlen(error_message));
	free(error_message);
}

static char	*join_three_strs(char *s1, char *s2, char *s3)
{
	char	*tmp1;
	char	*tmp2;

	tmp1 = ft_strjoin(s1, s2);
	tmp2 = ft_strjoin(tmp1, s3);
	free(tmp1);
	return (tmp2);
}
