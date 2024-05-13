/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:28:47 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/05/13 20:22:29 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*allocate_tenv(char *env_line);
static int		get_env_len(char *env_line, int *key_value_len);

t_env	*get_key_value(char *env_line)
{
	t_env	*env_node;
	int		index;
	int		value_index;

	index = 0;
	value_index = 0;
	env_node = allocate_tenv(env_line);
	if (env_node == NULL)
		return (NULL);
	while (env_line[index] != '=' && env_line[index] != '\0')
	{
		env_node->key[index] = env_line[index];
		index++;
	}
	env_node->key[index] = '\0';
	if (env_line[index] == '=')
		index++;
	while (env_line[index] != '\0')
	{
		env_node->value[value_index] = env_line[index];
		index++;
		value_index ++;
	}
	env_node->value[value_index] = '\0';
	return (env_node);
}

static t_env	*allocate_tenv(char *env_line)
{
	int		key_value_len[2];
	t_env	*env_node;

	if (get_env_len(env_line, &key_value_len[0]) != 0)
		return (NULL);
	env_node = (t_env *)malloc(sizeof(t_env) * 1);
	if (env_node == NULL)
		return (NULL);
	env_node->key = (char *)malloc(sizeof(char) * (key_value_len[0] + 1));
	if (env_node->key == NULL)
	{
		free(env_node);
		return (NULL);
	}
	env_node->value = (char *)malloc(sizeof(char) * (key_value_len[1] + 1));
	if (env_node->value == NULL)
	{
		free(env_node);
		free(env_node->key);
		return (NULL);
	}
	env_node->next = NULL;
	return (env_node);
}

static int	get_env_len(char *env_line, int *key_value_len)
{
	if (env_line == NULL || key_value_len == NULL)
		return (-1);
	key_value_len[0] = 0;
	key_value_len[1] = 0;
	while (env_line[key_value_len[0]] != '=' \
		&& env_line[key_value_len[0]] != '\0')
		key_value_len[0]++;
	if (env_line[key_value_len[0]] == '\0')
		return (1);
	while (env_line[key_value_len[0] + key_value_len[1] + 1] != '\0')
		key_value_len[1]++;
	if (key_value_len[1] == 0)
		return (1);
	return (0);
}
