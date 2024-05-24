/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 20:21:36 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/05/24 17:33:51 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*free_env(t_env *env)
{
	t_env	*current;
	t_env	*for_free;

	current = env;
	while (current != NULL)
	{
		for_free = current;
		current = current->next;
		free_node(for_free);
	}
	return (NULL);
}

void	free_node(t_env *node)
{
	if (node == NULL)
		return ;
	if (node->key != NULL)
		free(node->key);
	if (node->value != NULL)
		free(node->value);
	free(node);
}
