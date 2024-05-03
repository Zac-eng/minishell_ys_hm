/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 21:07:32 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/05/03 22:45:04 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_envnode(t_env *node);

void	_unset(t_env **env, char *name)
{
	t_env	*current;
	t_env	*for_free;

	if (env == NULL || name == NULL)
		return ;
	if (*env == NULL)
		return ;
	current = *env;
	if (is_equal((*env)->key, name) == 1)
	{
		*env = (*env)->next;
		free_envnode(current);
		return ;
	}
	while (current->next != NULL && is_equal(current->next->key, name) == 0)
		current = current->next;
	if (current->next != NULL)
	{
		for_free = current->next;
		current->next = current->next->next;
		free_envnode(for_free);
	}
}

static void	free_envnode(t_env *node)
{
	free(node->key);
	free(node->value);
	free(node);
}
