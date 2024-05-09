#include "minishell.h"

void *parser_check(t_token **tmp, t_parser **parser_tmp, t_parser **parser)
{
	// パーサーがあるかどうか見てる
	if ((*tmp)->kind == PIPE)
	{
		if (parser_pipe(parser_tmp, *parser) == NULL)
			return (NULL);
	}
	else if (is_redirect(*tmp_token) == true)
	{
		if (parser_redirect(tmp, parser_tmp) == NULL)

			return ;
	}
	else
	{
		if (parser_cmd(tmp,parser_tmp) == NULL)
		return ;
	}
	return (parser_tmp);
}

t_parser	*parser(t_token	*lexer)
{
	t_token	*tmp;
	t_parser *parser;
	t_parser *parser_tmp;

	tmp = lexer;
	token_check(lexer);
	while (tmp->next != NULL)
	{
		if (parser_check(&tmp, &parser_tmp, &parser) == NULL)
			return (NULL);
		parser_tmp = parser_tmp->next;
	}
}