/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:12:46 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/05/13 18:12:47 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_parser(t_parser **parser)
{
	t_parser	*tmp;
	t_parser	*delete;
}

void	*parser_pipe(t_parser **parser_tmp, t_parser **parser)
{
	(*parser_tmp)->next = parser_node_new();
	if ((*parser_tmp)->next == NULL)
	{
		exit(0);
	}
	(*parser_tmp)->next->prev = *parser_tmp;
	(*parser_tmp) = (*parser_tmp)->next;
	return (*parser_tmp);
}
