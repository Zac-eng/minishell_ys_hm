/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 20:18:16 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/07/10 20:28:06 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	perror_set_flag(void)
{
	perror("minishell");
	g_flag = 1;
}

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
	else if (error_code == PARSE_ERROR_REDIRECT_STR)
		printf("minishell: syntax error near unexpected token `%s'\n", insert);
	else if (error_code == PARSE_ERROR_REDIRECT)
		printf("minishell: syntax error near unexpected 'newline'\n");
	g_flag = error_code;
}

void	put_error_exit(t_code error_code)
{
	if (error_code == FORK_ERROR)
		printf("fork failed: resource temporarily unavailable\n");
	exit(error_code);
}
