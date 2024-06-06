/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 21:07:32 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/06/06 11:00:25 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_unset(char **cmd, t_env **env)
{
	t_env	*current;

	if (env == NULL || *env == NULL || cmd == NULL || cmd[0] == NULL)
		return ;
	if (cmd[1] == NULL)
		return ;
	current = *env;
	if (is_equal((*env)->key, "_") != 1 && is_equal((*env)->key, cmd[1]) == 1)
	{
		*env = (*env)->next;
		free_node(current);
		return ;
	}
	while (current->next != NULL && is_equal(current->next->key, "_") == 0 && \
									is_equal(current->next->key, cmd[1]) == 0)
		current = current->next;
	if (is_equal(current->next->key, "_") == 0 && \
									is_equal(current->next->key, cmd[1]) == 1)
		remove_env(current);
}
