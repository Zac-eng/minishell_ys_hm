/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 20:02:22 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/05/30 20:11:47 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	insert_env(t_env *previous, t_env *to_insert)
{
	t_env	*current_next;

	if (previous == NULL || to_insert == NULL)
		return (-1);
	current_next = previous->next;
	previous->next = to_insert;
	to_insert->next = current_next;
	return (0);
}

int	remove_env(t_env *previous)
{
	t_env	*for_free;

	if (previous == NULL || previous->next == NULL)
		return (-1);
	for_free = previous->next;
	previous->next = for_free->next;
	free_node(for_free);
	return (0);
}
