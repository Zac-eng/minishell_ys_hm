/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 18:42:37 by yususato          #+#    #+#             */
/*   Updated: 2024/02/01 15:04:17 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_stack	*create_stack(void)
{
	t_stack	*new;

	new = (t_stack *)malloc(sizeof(t_stack));
	if (new == NULL)
		exit(1);
	new->top = NULL;
	new->bottom = NULL;
	new->current = 0;
	return (new);
}

void	push(t_stack *stack, char *line, int type)
{
	t_node		*node;

	node = (t_node *)malloc(sizeof(t_node));
	if (node == NULL)
		exit(1);
	node->str = line;
	node->prev = NULL;
	node->next = stack->top;
	if (stack->top == NULL)
	{
		stack->top = node;
		stack->bottom = node;
	}
	else
	{
		stack->top->next = node;
		node->prev = stack->top;
		stack->top = node;
	}
	node->data = type;
	stack->current = stack->current +1;
}

int	pop(t_stack *stack)
{
	t_node	*node;
	int		data;

	if (!(stack->top))
		exit(1);
	node = stack->top;
	data = node->data;
	if (stack->top == stack->bottom)
	{
		stack->top = NULL;
		stack->bottom = NULL;
	}
	else
	{
		stack->top = stack->top->prev;
		stack->top->next = NULL;
	}
	stack->current = stack->current - 1;
	free(node);
	return (data);
}
