/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redirect.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:12:51 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/05/13 18:16:44 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	file_init(t_file **file, char *file_name, t_token_kind kind, \
												t_token_kind next_kind)
{
	(*file) = (t_file *)malloc(sizeof(t_file));
	if ((*file) == NULL)
		ft_exit();
	(*file)->next = NULL;
	(*file)->file_name = strdup(file_name);
	if (kind == D_LESSER && is_quote(next_kind) == true)
		(*file)->type = QUOTE_HEREDOC;
	else if (kind == D_LESSER)
		(*file)->type = HEREDOC;
	else if (kind == S_LESSER)
		(*file)->type = IN_FILE;
	else if (kind == D_GREATER)
		(*file)->type = APPEND;
	else if (kind == S_GREATER)
		(*file)->type = OUT_FILE;
	return (file);
}

void	file_add(t_file **file, char *file_name, t_token_kind kind, \
												t_token_kind next_kind)
{
	while ((*file)->next != NULL)
		(*file) = (*file)->next;
	(*file)->next = (t_file *)malloc(sizeof(t_file));
	if ((*file) == NULL)
		ft_exit();
	(*file) = (*file)->next;
	(*file)->next = NULL;
	(*file)->file_name = strdup(file_name);
	if (kind == D_LESSER && is_quote(next_kind) == true)
		(*file)->type = QUOTE_HEREDOC;
	else if (kind == D_LESSER)
		(*file)->type = HEREDOC;
	else if (kind == S_LESSER)
		(*file)->type = IN_FILE;
	else if (kind == D_GREATER)
		(*file)->type = APPEND;
	else if (kind == S_GREATER)
		(*file)->type = OUT_FILE;
	return (file);
}

void	parser_output(t_token **lexer_tmp, t_parser **parser_tmp)
{
	if ((*parser_tmp)->file == NULL)
		file_init(&(*parser_tmp)->file, (*lexer_tmp)->nexr->str, \
					(*lexer_tmp)->kind, (*lexer_tmp)->nexr->kind);
	else
		file_add(&(*parser_tmp)->file, (*lexer_tmp)->nexr->str, \
					(*lexer_tmp)->kind, (*lexer_tmp)->nexr->kind);
}

void	parser_input(t_token **lexer_tmp, t_parser **parser_tmp)
{
	if ((*parser_tmp)->file == NULL)
		file_init(&(*parser_tmp)->file, (*lexer_tmp)->nexr->str, \
					(*lexer_tmp)->kind, (*lexer_tmp)->nexr->kind);
	else
		file_add(&(*parser_tmp)->file, (*lexer_tmp)->nexr->str, \
					(*lexer_tmp)->kind, (*lexer_tmp)->nexr->kind);
}

void	parser_redirect(t_token **lexer_tmp, t_parser **parser_tmp)
{
	if ((*lexer_tmp)->type == TK_LESS || (*lexer_tmp)->type == TK_DLESS)
	{
		parser_output(lexer_tmp, parser_tmp);
	}
	else if ((*lexer_tmp)->type == TK_GREAT || (*lexer_tmp)->type == TK_DGREAT)
	{
		parser_input(lexer_tmp, parser_tmp);
	}
	*lexer_tmp = (*lexer_tmp)->next;
	return ;
}
