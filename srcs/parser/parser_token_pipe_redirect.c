/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token_pipe_redirect.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 20:55:05 by yususato          #+#    #+#             */
/*   Updated: 2024/07/12 19:09:48 by yususato         ###   ########.fr       */
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
				return (put_error(PARSE_ERROR_REDIRECT_STR \
				, tmp->next->str), false);
		}
		else
			tmp = tmp->next;
	}
	if (tmp != NULL && lexer_connect_check(tmp) == false)
		return (false);
	return (true);
}
