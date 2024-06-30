/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:17:01 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/06/26 16:24:19 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	start_check(t_token *tmp, t_env **env)
{
	if (tmp->kind == TK_CMD || tmp->kind == TK_SQUOTE || tmp->kind == TK_DQUOTE)
		return (true);
	return (false);
}

bool	connect_check(t_token *tmp, t_env **env)
{
	if (tmp->kind == TK_CMD || tmp->kind == TK_SQUOTE || tmp->kind == TK_DQUOTE)
		return (true);
	return (false);
}

void	node_delete(t_token *tmp, t_token *tmp_next)
{
	t_token	*tmp2;

	tmp2 = tmp_next->next;
	tmp->space_flag = tmp_next->space_flag;
	tmp->next = tmp2;
	free(tmp_next->str);
	free(tmp_next);
}

void	token_check(t_token	*lexer, t_env **env)
{
	t_token	*tmp;
	t_token	*tmp2;
	char	*new;

	tmp = lexer;
	tmp2 = lexer;
	while (tmp->next != NULL && tmp != NULL)
	{
		if (tmp->space_flag == false)
		{
			if (start_check(tmp, env) && connect_check(tmp->next, env))
			{
				new = ft_strjoin(tmp->str, tmp->next->str);
				if (new == NULL)
					exit(0);
				free(tmp->str);
				tmp->str = new;
				node_delete(tmp, tmp->next);
			}
			else
				tmp = tmp->next;
		}
		else
			tmp = tmp->next;
	}
}
