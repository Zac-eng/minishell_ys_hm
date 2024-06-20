/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 09:55:42 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/06/20 10:45:24 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_env(t_env *env, bool is_export)
{
	t_env	*current;

	g_flag = 0;
	if (env == NULL)
		return ;
	current = env;
	while (current != NULL)
	{
		if (is_export)
			printf("declare -x %s=\"%s\"\n", current->key, current->value);
		else
			printf("%s=%s\n", current->key, current->value);
		current = current->next;
	}
}
