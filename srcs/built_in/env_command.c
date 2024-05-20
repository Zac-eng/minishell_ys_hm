/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_command.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 09:55:42 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/05/20 21:40:52 by hmiyazak         ###   ########.fr       */
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
	t_env	*env_head_tail[2];
	t_env	*env_tmp;
	int		env_index;

	env_index = 0;
	env_head_tail[0] = NULL;
	env_head_tail[1] = NULL;
	if (env == NULL)
		exit(1);
	while (env[env_index] != NULL)
	{
		env_tmp = get_key_value(env[env_index]);
		if (env_tmp == NULL)
		{
			free_env(env_head_tail[0]);
			exit(1);
		}
		if (env_head_tail[0] == NULL)
			env_head_tail[0] = env_tmp;
		if (env_head_tail[1] != NULL)
			env_head_tail[1]->next = env_tmp;
		env_head_tail[1] = env_tmp;
		env_index++;
	}
	return (env_head_tail[0]);
}

// char	**env_into_list(t_env *env)
// {
// 	if (env == NULL)
// 		return (NULL);

// }
