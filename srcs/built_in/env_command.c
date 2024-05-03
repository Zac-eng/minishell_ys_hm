/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 09:55:42 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/05/03 21:17:10 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_env(t_env *env)
{
	t_env	*current;

	if (env == NULL)
		return ;
	current = env;
	while (current != NULL)
	{
		printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}

t_env	*env_into_tenv(char **env)
{
	t_env	*env_head;
	t_env	*env_tail;
	t_env	*env_tmp;
	int		env_index;

	env_index = 0;
	env_head = NULL;
	env_tail = NULL;
	if (env == NULL)
		return (NULL);
	while (env[env_index] != NULL)
	{
		env_tmp = get_key_value(env[env_index]);
		if (env_tmp == NULL)
			return (free_env(env_head));
		if (env_head == NULL)
			env_head = env_tmp;
		if (env_tail != NULL)
			env_tail->next = env_tmp;
		env_tail = env_tmp;
		env_index++;
	}
	return (env_head);
}

// char	**env_into_list(t_env *env)
// {
// 	if (env == NULL)
// 		return (NULL);

// }
