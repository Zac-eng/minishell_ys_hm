/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:12:03 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/05/13 18:38:45 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_redirect(t_token *lexer_tmp)
{
	if (tmp->token == TK_LESS || tmp->token == TK_DLESS \
		|| tmp->token == TK_GREAT || tmp->token == TK_DGREAT)
		return (true);
	else
		return (false);
}

bool	is_quote(t_token_kind kind)
{
	if (tmp->token == TK_SQUOTE || tmp->token == TK_DQUOTE)
		return (true);
	else
		return (false);
}