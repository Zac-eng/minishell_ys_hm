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

void	*parser_pipe(t_parser **parser_tmp, t_parser **parser)
{
	(*parser_tmp)->next = parser_node_new();
	if ((*parser_tmp)->next == NULL)
	{
		free_parser(parser);
		ft_exit();
	}
	(*parser_tmp) = (*parser_tmp)->next;
	return (*parser_tmp);
}

t_parser	parser_node_new(void)
{
	t_parser	*new;

	new = (t_parser *)malloc(sizeof(t_parser));
	if (new == NULL)
		ft_exit();
	new->next = NULL;
	new->cmd = NULL;
	new->file = NULL;
	return (new);
}
