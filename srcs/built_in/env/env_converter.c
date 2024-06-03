/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_handler.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 19:53:15 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/05/30 19:54:48 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*flatten_tenv(t_env *env);
static int	get_tenv_len(t_env *env);

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

char	**env_into_list(t_env *env)
{
	char	**env_list;
	t_env	*current;
	int		env_len;
	int		index;

	if (env == NULL)
		return (NULL);
	current = env;
	index = 0;
	env_len = get_tenv_len(env);
	if (env_len < 0)
		return (NULL);
	env_list = (char **)malloc(sizeof(char *) * (env_len + 1));
	if (env_list == NULL)
		return (NULL);
	while (current != NULL)
	{
		env_list[index] = flatten_tenv(current);
		if (env_list[index] == NULL)
			exit(1);
		current = current->next;
		index++;
	}
	env_list[index] = NULL;
	return (env_list);
}

static char	*flatten_tenv(t_env *env)
{
	char	*line;
	int		len;

	len = 0;
	len += ft_strlen(env->key);
	len += ft_strlen(env->value);
	line = (char *)malloc(sizeof(char) * (len + 1));
	if (line == NULL)
		return (NULL);
	ft_strlcpy(line, env->key, ft_strlen(env->key));
	ft_strlcpy(line, env->value, ft_strlen(env->value));
	line[len] = '\0';
	return (line);
}

static int	get_tenv_len(t_env *env)
{
	t_env	*current;
	int		len;

	if (env == NULL)
		return (-1);
	current = env;
	len = 0;
	while (current != NULL)
	{
		current = current->next;
		len++;
	}
	return (len);
}
