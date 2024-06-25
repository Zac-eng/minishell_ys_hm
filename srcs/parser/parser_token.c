/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:17:01 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/06/25 19:47:36 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h";

void	expand_env()

void	expand_cmd(t_token *tmp)
{
	int	i;

	i = 0;
	while (tmp->str[i])
	{
		if (tmp->str[i] == '$')
			expand_env(&tmp->str[i]);
		i++;
	}
}

void	expand(t_token *tmp)
{
	if (tmp->kind == TK_CMD)
		expand_cmd(tmp);
	else if (tmp->kind == TK_SQUOTE)
		expand_squote(tmp);
	else if (tmp->kind == TK_DQUOTE)
		expand_dquote(tmp);
}

bool	start_check(t_token *tmp)
{
	if (tmp->kind == TK_CMD || tmp->kind == TK_SQUOTE || tmp->kind == TK_DQUOTE)
	{
		expand(tmp);
		return (true);
	}
	return (false);
}

bool	connect_check(t_token *tmp)
{
	if (tmp->kind == TK_CMD || tmp->kind == TK_SQUOTE || tmp->kind == TK_DQUOTE)
	{
		expand(tmp);
		return (true);
	}
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

	tmp = lexer;
	tmp2 = lexer;
	while (tmp->next != NULL && tmp != NULL)
	{
		if (tmp->space_flag == false)
		{
			if (start_check(tmp) && connect_cheack(tmp->next))
			{
				ft_strjoin(tmp->str, tmp->next->str);
				node_delete(tmp, tmp->next);
			}
		}
		else
			tmp = tmp->next;
	}
}
