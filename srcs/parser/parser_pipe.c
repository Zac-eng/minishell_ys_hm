/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:12:46 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/07/07 22:08:17 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	free_parser(t_parser **parser)
// {
// 	t_parser	*tmp;
// 	t_parser	*delete;
// }

void	*parser_pipe(t_parser **parser_tmp, t_parser **parser)
{
	(void)parser;
	(*parser_tmp)->next = parser_node_new();
	if ((*parser_tmp)->next == NULL)
		return (NULL);
	(*parser_tmp)->next->prev = *parser_tmp;
	(*parser_tmp) = (*parser_tmp)->next;
	return (*parser_tmp);
}
