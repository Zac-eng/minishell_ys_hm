/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 20:18:16 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/06/17 22:07:30 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	put_error(t_code error_code, char *insert)
{
	if (error_code == FILE_ERROR)
		printf("%s: Too many open files\n", insert);
	else if (error_code == NOT_FOUND_ERROR)
		printf("minishell: %s: command not found\n", insert);
	else if (error_code == NO_FILE_ERROR)
		printf("minishell: %s: No such file or directory\n", insert);
	else if (error_code == PARSE_ERROR)
		printf("minishell: syntax error near unexpected token `%c'\n", *insert);
	g_status = error_code;
}

void	put_error_exit(t_code error_code)
{
	if (error_code == FORK_ERROR)
		printf("fork failed: resource temporarily unavailable\n");
	exit(error_code);
}
