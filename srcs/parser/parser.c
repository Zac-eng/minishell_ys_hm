/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:18:10 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/06/30 13:43:46 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	parser_error(t_parser *parser_head, char *current_str);

t_parser	*parser(t_token	*lexer, t_env **env)
{
	t_token		*lexer_tmp;
	t_parser	*parser;
	t_parser	*parser_tmp;

	if (lexer == NULL)
		return (NULL);
	expand(lexer, env);
	token_check(lexer, env);
	lexer_tmp = lexer;
	parser = parser_node_new();
	if (parser == NULL)
		return (NULL);
	parser_tmp = parser;
	while (lexer_tmp != NULL)
	{
		if (parser_check(&lexer_tmp, &parser_tmp, &parser, env) == NULL)
			return (parser_error(parser, lexer_tmp->str), NULL);
		lexer_tmp = lexer_tmp->next;
	}
	return (parser);
}

void	*parser_check(t_token **lexer_tmp, t_parser **parser_tmp, \
											t_parser **parser, t_env **env)
{
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
		if (parser_cmd(lexer_tmp, parser_tmp) == NULL)
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

static void	parser_error(t_parser *parser_head, char *current_str)
{
	char	current;

	free_parser(parser_head);
	if (current_str == NULL)
		current = '\0';
	else
		current = *current_str;
	put_error(PARSE_ERROR, &current);
}
