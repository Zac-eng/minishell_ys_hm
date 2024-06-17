/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 20:16:45 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/06/16 14:56:00 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_parser(t_parser *parser_head)
{
	t_parser	*current;
	t_parser	*tmp;

	current = parser_head;
	while (current != NULL)
	{
		tmp = current;
		current = current->next;
		free_str_list(tmp->cmd);
		if (tmp->file != NULL)
			free(tmp->file);
		free(tmp);
	}
}