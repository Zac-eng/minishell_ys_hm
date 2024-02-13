/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 09:56:06 by yususato          #+#    #+#             */
/*   Updated: 2024/02/11 18:40:08 by yususato         ###   ########.fr       */
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
	t_token	*parent;
	t_token	*tmp;
	int		flag;

	flag = 0;
	tmp = token;
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
	if (flag > 0)
	{
		while (tmp->str == ';')
		{
			if (tmp->str == '|')
			{
				tmp = tmp->prev;
				break ;
			}
		}
		parent->next = tmp;
	}
	 
	else if (flag == 1)
	{
		if (tmp->str == '|')
			{
				tmp = tmp->prev;
				break;
			}
		token = token->next
	}
	
}
