#include "minishell.h"

void *parser_check(t_token **lexer_tmp, t_parser **parser_tmp, t_parser **parser)
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
			return ;
	}
	else
	{
		if (parser_cmd(lexer_tmp,parser_tmp) == NULL)
		return ;
	}
	return (parser_tmp);
}

t_parser	*parser(t_token	*lexer)
{
	t_token	*lexer_tmp;
	t_parser *parser;
	t_parser *parser_tmp;

	tmp = lexer;
	// token_check(lexer);
	parser = paser_node_new();
	while (tmp->next != NULL)
	{
		if (parser_check(&lexer_tmp, &parser_tmp, &parser) == NULL)
			return (NULL);
		lexer_tmp = lexer_tmp->next;
	}
}
