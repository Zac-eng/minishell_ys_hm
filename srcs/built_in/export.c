/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 21:07:07 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/05/03 22:11:48 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_export(t_env **env_head, char *env_line)
{
	t_env	*new_node;
	t_env	*current_node;

	if (env_head == NULL)
		return ;
	if (env_line == NULL)
		_env(*env_head);
	new_node = get_key_value(env_line);
	if (new_node == NULL)
		return ;
	if (*env_head == NULL)
	{
		*env_head = new_node;
		return ;
	}
	else
	{
		current_node = *env_head;
		while (current_node->next != NULL)
			current_node = current_node->next;
		current_node->next = new_node;
		printf("%s, %s\n", new_node->key, new_node->value);
	}
}
