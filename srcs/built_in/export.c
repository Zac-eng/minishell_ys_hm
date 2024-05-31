/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 21:07:07 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/05/31 13:42:31 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*find_node(t_env *env_head, char *key);
static void		add_env(t_env *env_head, t_env *new_node);
static int		rewrite_value(char **before, char *after);

void	_export(char **cmd, t_env **env_head)
{
	t_env	*new_node;
	t_env	*target;

	if (cmd == NULL || env_head == NULL)
		return ;
	if (cmd[1] == NULL)
		return (_env(*env_head));
	new_node = get_key_value(cmd[1]);
	if (new_node == NULL)
		return ;
	if (*env_head == NULL)
	{
		*env_head = new_node;
		return ;
	}
	target = find_node(*env_head, new_node->key);
	if (target == NULL)
		add_env(*env_head, new_node);
	else
	{
		if (rewrite_value(&target->value, new_node->value) < 0)
			return ;
		free_node(new_node);
	}
}

static void	add_env(t_env *env_head, t_env *new_node)
{
	t_env	*current;
	t_env	*current_next;

	if (env_head == NULL || new_node == NULL)
		return ;
	current = env_head;
	if (current == NULL)
		return ;
	while (current->next != NULL && is_equal(current->next->key, "_") == 0)
		current = current->next;
	current_next = current->next;
	current->next = new_node;
	new_node->next = current_next;
}

static t_env	*find_node(t_env *env_head, char *key)
{
	t_env	*current;

	if (env_head == NULL || key == NULL)
		return (NULL);
	current = env_head;
	while (is_equal(current->key, key) != 1 && \
		current->next != NULL && is_equal(current->next->key, "_") != 1)
		current = current->next;
	if (is_equal(current->key, key) == 1)
		return (current);
	else
		return (NULL);
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
