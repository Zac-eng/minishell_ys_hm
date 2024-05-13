/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:18:10 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/05/13 18:40:25 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*parser_check(t_token **lexer_tmp, t_parser **parser_tmp, \
													t_parser **parser)
{
	// パーサーがあるかどうか見てる
	if ((*tmp)->kind == PIPE)
	{
		if (parser_pipe(parser_tmp, *parser) == NULL)
			return (NULL);
	}
	else if (is_redirect((*lexer_tmp)) == true)
	{
		if (parser_redirect(lexer_tmp, parser_tmp) == NULL)
			return (NULL);
	}
	else
	{
		if (parser_cmd(lexer_tmp, parser_tmp) == NULL)
			return (NULL);
	}
	return (parser_tmp);
}

t_parser	*parser(t_token	*lexer)
{
	t_token		*lexer_tmp;
	t_parser	*parser;
	t_parser	*parser_tmp;

	tmp = lexer;
	// token_check(lexer);
	parser = paser_node_new();
	while (tmp->next != NULL)
	{
		if (parser_check(&lexer_tmp, &parser_tmp, &parser) == NULL)
			return (NULL);
		lexer_tmp = lexer_tmp->next;
	}
	return (parser);
}
