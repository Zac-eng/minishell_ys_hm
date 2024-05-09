#include "minishell.h"

void file_init(t_parser parser_tmp)
{
	
}
void file_add(t_parser parser_tmp)
{

}

void	parser_output(t_token **tmp, t_parser **parser_tmp)
{
	if ((*parser_tmp)->file == NULL)
	{
		file_init(parser_tmp, tmp)
	}
	else
		filr_add(parser_tmp, tmp);
}

void	parser_redirect(t_token **tmp, t_parser **parser_tmp)
{
	if ((*tmp)->type == TK_LESS || (*tmp)->type == TK_DLESS)
	{
		parser_output(tmp, parser_tmp);
	}
	else if ((*tmp)->type == TK_GREAT || (*tmp)->type == TK_DGREAT)
	{
		parser_input(tmp, parser_tmp);
	}
	*tmp = (*tmp)->next;
	return ;
}