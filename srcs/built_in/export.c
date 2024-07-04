/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 21:07:07 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/07/02 12:56:46 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef enum e_export {
	ADDITION,
	INVALID,
	EQUAL,
}	t_export;
static void		export_action(t_env **env_head, char *envvars, \
											t_export type);
static t_export	check_envvars(char *envvars);
static int		rewrite_value(char **before, char *after, t_export type);

void	_export(char **cmd, t_env **env_head)
{
	t_export	type;
	int			envvar_index;

	g_flag = 0;
	envvar_index = 1;
	if (cmd == NULL || env_head == NULL)
		return ;
	if (cmd[1] == NULL)
		return (_env(*env_head, true));
	while (cmd[envvar_index] != NULL)
	{
		type = check_envvars(cmd[envvar_index]);
		if (type == INVALID)
		{
			write(2, "not a valid identifier\n", 23);
			g_flag = 1;
			envvar_index++;
			continue ;
		}
		export_action(env_head, cmd[envvar_index], type);
		envvar_index++;
	}
}

static void	export_action(t_env **env_head, char *envvars, t_export type)
{
	t_env	*target;
	t_env	*new_node;

	if (envvars == NULL)
		return ;
	new_node = create_envnode(envvars);
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
		rewrite_value(&target->value, new_node->value, type);
		free_node(new_node);
	}
}

static t_export	check_envvars(char *envvars)
{
	int	index;

	index = 0;
	if ('0' <= envvars[0] && envvars[0] <= '9')
		return (INVALID);
	while (envvars[index] != '\0' && envvars[index] != '=')
	{
		if (envvars[index] == '-' || envvars[index] == '%' || \
			envvars[index] == '/' || envvars[index] == ' ')
			return (INVALID);
		else if (envvars[index] == '+')
		{
			if (envvars[index + 1] == '=')
				return (ADDITION);
			else
				return (INVALID);
		}
		index++;
	}
	return (EQUAL);
}

static int	rewrite_value(char **before, char *after, t_export type)
{
	char	*tmp;

	if (before == NULL || after == NULL)
		return (-1);
	if (type == ADDITION)
	{
		tmp = *before;
		*before = ft_strjoin(*before, after);
		free(tmp);
		if (before == NULL)
			return (-1);
	}
	else
	{
		free(*before);
		*before = ft_strdup(after);
		if (before == NULL)
			return (-1);
	}
	return (0);
}
