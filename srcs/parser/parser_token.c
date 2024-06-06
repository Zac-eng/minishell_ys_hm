/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:17:01 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/05/13 18:17:39 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h";

bool	can_connect(t_token *next)
{
	// tmpと連結できるかを試す
	if (tmp->token == TK_CMD || tmp->token == TK_SQUOTE || tmp->token == TK_DQUOTE)
		return (true);
	else
		return (false);
}

bool	start_check(t_token *tmp)
{
	// はじめに来ていいトークンか見る
	// 左スペース、左ダブル、シングルクオート以外
	return (true);
	else
		return (false);
}

void	node_delete(t_token *tmp, t_token *tmp_next)
{
	t_token	*tmp2;

	tmp2 = tmp_next->next;
	tmp->next = tmp2;
	free(tmp_next->str);
	free(tmp_next->kind);
	free(tmp_next);
}

void	token_check(t_token	*lexer)
{
	t_token	*tmp;
	t_token	*tmp2;
	// 空白、パイプ、リダイレクトは独立させる

	tmp = lexer;
	tmp2 = lexer;
	while (tmp->next != NULL && tmp != NULL)
	{
		if (start_check(tmp) && can_connect(tmp->next))
		{
			strjoin(tmp->str, tmp->next->str);
			node_delete(tmp, tmp->next);
		}
		else
			tmp = tmp->next;
	}
}