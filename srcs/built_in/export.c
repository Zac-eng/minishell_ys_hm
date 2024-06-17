/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 21:07:07 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/06/17 19:56:26 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		rewrite_value(char **before, char *after);

void	_export(char **cmd, t_env **env_head)
{
	t_env	*new_node;
	t_env	*target;

	g_status = 0;
	if (cmd == NULL || env_head == NULL)
		return ;
	if (cmd[1] == NULL)
		return (_env(*env_head));
	new_node = create_envnode(cmd[1]);
	if (new_node == NULL)
		return ;
	if (*env_head == NULL)
	{
		*env_head = new_node;
		return ;
	}
	target = find_node(*env_head, new_node->key);
	if (target == NULL)
		push_env(*env_head, new_node);
	else
	{
		if (rewrite_value(&target->value, new_node->value) < 0)
			return ;
		free_node(new_node);
	}
}

static int	rewrite_value(char **before, char *after)
{
	char	*clone;
	int		index;

	index = 0;
	if (before == NULL || after == NULL)
		return (-1);
	free(*before);
	clone = (char *)malloc(sizeof(char) * (ft_strlen(after) + 1));
	if (clone == NULL)
		return (-1);
	while (after[index] != '\0')
	{
		clone[index] = after[index];
		index++;
	}
	clone[index] = '\0';
	*before = clone;
	return (0);
}
