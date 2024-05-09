#include "minishell.h"

t_token	*create_token(char *line, t_token_kind kind)
{
	t_token	*token;

	token = calloc(1, sizeof(*token));
	if (token == NULL)
		return (NULL);
	token->str = line;
	token->kind = kind;
	token->next = NULL;
	return (token);
}
