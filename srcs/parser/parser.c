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
													t_parser **parser, t_env **env)
{
	// パーサーがあるかどうか見てる
	if ((*lexer_tmp)->kind == TK_PIPE)
	{
		if (parser_pipe(parser_tmp, parser) == NULL)
			return (NULL);
	}
	else if (is_redirect((*lexer_tmp)) == true)
	{
		if (parser_redirect(lexer_tmp, parser_tmp) == NULL)
			return (NULL);
	}
	else
	{
		if (parser_cmd(lexer_tmp, parser_tmp, env) == NULL)
			return (NULL);
	}
	return (parser_tmp);
}

t_parser	*parser_node_new(void)
{
	t_parser	*new;

	new = (t_parser *)malloc(sizeof(t_parser));
	if (new == NULL)
		exit(1);
	new->next = NULL;
	new->prev = NULL;
	new->cmd = NULL;
	new->file = NULL;
	return (new);
}

t_parser	*parser(t_token	*lexer, t_env **env)
{
	t_token		*lexer_tmp;
	t_parser	*parser;
	t_parser	*parser_tmp;

	lexer_tmp = lexer;
	// token_check(lexer);
	parser = parser_node_new();
	if (parser == NULL)
		return (NULL);
	parser_tmp = parser;
	while (lexer_tmp != NULL)
	{
		if (parser_check(&lexer_tmp, &parser_tmp, &parser, env) == NULL)
			return (NULL);
		lexer_tmp = lexer_tmp->next;
	}
	return (parser);
}
