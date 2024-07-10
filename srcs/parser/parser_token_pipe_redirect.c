/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token_pipe_redirect.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:55:05 by yususato          #+#    #+#             */
/*   Updated: 2024/07/10 13:13:09 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	start_check_pipe_redirect(t_token *tmp)
{
	if (is_pipe_redirect(tmp))
		return (true);
	return (false);
}

bool	connect_check_pipe_redirect(t_token *tmp)
{
	if (is_pipe_redirect(tmp))
		return (true);
	return (false);
}

bool	token_check_pipe_redirect(t_token *lexer)
{
	t_token	*tmp;

	tmp = lexer;
	while (tmp->next != NULL && tmp != NULL)
	{
		if (start_check_pipe_redirect(tmp) \
			&& connect_check_pipe_redirect(tmp->next))
		{
			if (tmp->kind == TK_PIPE || tmp->next->kind == TK_PIPE)
				return (put_error(PARSE_ERROR, "|"), false);
			else
				return (put_error(PARSE_ERROR_REDIRECT, ""), false);
			tmp = tmp->next;
			continue ;
		}
		else
		{
			tmp = tmp->next;
			continue ;
		}
	}
	if (tmp != NULL && lexer_connect_check(tmp) == false)
		return (false);
	return (true);
}
