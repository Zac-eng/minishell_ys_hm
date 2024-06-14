/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:12:51 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/06/14 21:04:49 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	file_init(t_file **file, char *file_name, t_token_kind kind, \
												t_token_kind next_kind)
{
	(*file) = (t_file *)malloc(sizeof(t_file));
	if ((*file) == NULL)
		exit(1);
	(*file)->next = NULL;
	(*file)->file_name = strdup(file_name);
	if (kind == TK_DLESS && is_quote(next_kind) == true)
		(*file)->type = QUOTE_HEREDOC;
	else if (kind == TK_DLESS)
		(*file)->type = HEREDOC;
	else if (kind == TK_LESS)
		(*file)->type = IN_FILE;
	else if (kind == TK_DGREAT)
		(*file)->type = APPEND;
	else if (kind == TK_GREAT)
		(*file)->type = OUT_FILE;
	return ;
}

void	file_add(t_file **file, char *file_name, t_token_kind kind, \
												t_token_kind next_kind)
{
	while ((*file)->next != NULL)
		(*file) = (*file)->next;
	(*file)->next = (t_file *)malloc(sizeof(t_file));
	if ((*file) == NULL)
		exit(1);
	(*file) = (*file)->next;
	(*file)->next = NULL;
	(*file)->file_name = ft_strdup(file_name);
	if (kind == TK_DLESS && is_quote(next_kind) == true)
		(*file)->type = QUOTE_HEREDOC;
	else if (kind == TK_DLESS)
		(*file)->type = HEREDOC;
	else if (kind == TK_LESS)
		(*file)->type = IN_FILE;
	else if (kind == TK_DGREAT)
		(*file)->type = APPEND;
	else if (kind == TK_GREAT)
		(*file)->type = OUT_FILE;
	return ;
}

void	parser_output(t_token **lexer_tmp, t_parser **parser_tmp)
{
	if ((*parser_tmp)->file == NULL)
		file_init(&(*parser_tmp)->file, (*lexer_tmp)->next->str, \
					(*lexer_tmp)->kind, (*lexer_tmp)->next->kind);
	else
		file_add(&(*parser_tmp)->file, (*lexer_tmp)->next->str, \
					(*lexer_tmp)->kind, (*lexer_tmp)->next->kind);
}

void	parser_input(t_token **lexer_tmp, t_parser **parser_tmp)
{
	if ((*parser_tmp)->file == NULL)
		file_init(&(*parser_tmp)->file, (*lexer_tmp)->next->str, \
					(*lexer_tmp)->kind, (*lexer_tmp)->next->kind);
	else
		file_add(&(*parser_tmp)->file, (*lexer_tmp)->next->str, \
					(*lexer_tmp)->kind, (*lexer_tmp)->next->kind);
}

void	*parser_redirect(t_token **lexer_tmp, t_parser **parser_tmp)
{
	if ((*lexer_tmp)->kind == TK_LESS || (*lexer_tmp)->kind == TK_DLESS)
		parser_output(lexer_tmp, parser_tmp);
	else if ((*lexer_tmp)->kind == TK_GREAT || (*lexer_tmp)->kind == TK_DGREAT)
		parser_input(lexer_tmp, parser_tmp);
	*lexer_tmp = (*lexer_tmp)->next;
	return (parser_tmp);
}
