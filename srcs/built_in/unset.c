/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 21:07:32 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/05/09 19:54:54 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_envnode(t_env *node);

void	_unset(char **cmd, t_env **env)
{
	t_env	*current;
	t_env	*for_free;

	if (env == NULL || *env == NULL || cmd == NULL || cmd[0] == NULL)
		return ;
	if (cmd[1] == NULL)
		return ;
	current = *env;
	if (is_equal((*env)->key, cmd[1]) == 1)
	{
		*env = (*env)->next;
		free_envnode(current);
		return ;
	}
	while (current->next != NULL && is_equal(current->next->key, cmd[1]) == 0)
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
