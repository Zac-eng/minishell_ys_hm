/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 09:56:06 by yususato          #+#    #+#             */
/*   Updated: 2024/02/19 18:29:51 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*get_tree(t_token *token)
{
	t_token	*parent;
	t_token	*tmp;
	while (token->prev != NULL)
	{
		if (token->str == ';')
		{
			if (flag == 0)
			{
				parent = token;
			}
			else
				parent->prev = token;
			flag++;
		}	
		token = token->prev;
	}
}

void	parser(t_token *token)
{
	if (token->kind == PIPE)
		pipe();
	else if (token->kind == RED)
		red();
	else
		cmd();
}
 simple_cmd
 cmd
 redirection
 pipe
 args
 file path