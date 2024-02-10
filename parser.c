/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 09:56:06 by yususato          #+#    #+#             */
/*   Updated: 2024/02/01 12:50:51 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node	*get_tree(t_node *node)
{
	t_node	*parent;
	t_node	*tmp;
	while (node->prev != NULL)
	{
		if (node->str == ';')
		{
			if (flag == 0)
			{
				parent = node;
			}
			else
				parent->prev = node;
			flag++;
		}	
		node = node->prev;
	}
}

void	parser(t_node *node)
{
	t_node	*parent;
	t_node	*tmp;
	int		flag;

	flag = 0;
	tmp = node;
	while (node->prev != NULL)
	{
		if (node->str == ';')
		{
			if (flag == 0)
			{
				parent = node;
			}
			else
				parent->prev = node;
			flag++;
		}	
		node = node->prev;
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
		node = node->next
	}
	
}
