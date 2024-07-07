/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:54:01 by yususato          #+#    #+#             */
/*   Updated: 2024/07/07 20:27:34 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	question_add_len(int *i)
{
	int		len;
	char	*tmp;

	tmp = ft_itoa(g_flag);
	len = ft_strlen(tmp);
	*i += 2;
	free(tmp);
	return (len);
}

int	env_add_len(char *str, t_env **env, int *i)
{
	char	*head_env;
	int		len;
	char	*tmp;

	len = 0;
	len = is_squote_space(str);
	*i += len + 1;
	tmp = ft_substr(str, 0, len);
	if (!tmp)
		exit(0);
	head_env = _getenv(*env, tmp);
	if (!head_env)
		return (0);
	free(tmp);
	len = ft_strlen(head_env);
	return (len);
}

int	cmd_len(char *str, t_env **env)
{
	int		i;
	int		count;
	int		tmp;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] && str[i + 1] == '?')
			{
				tmp = question_add_len(&i);
				count += tmp;
			}
			else
			{
				tmp = env_add_len(&str[i + 1], env, &i);
				count += tmp;
			}
		}
		else
			simple_counter(&i, &count);
	}
	return (count);
}

int	env_question_add(char *new, int *i, int *count)
{
	int		len;
	char	*tmp;

	tmp = ft_itoa(g_flag);
	len = ft_strlen(tmp);
	*i += 2;
	str_insert(new, tmp);
	free(tmp);
	*count = *count + len;
	return (len);
}

int	parser_env_add(char *str, t_env **env, char *new, int *i)
{
	char	*env_value;
	int		len;
	char	*tmp;

	len = 0;
	len = is_squote_space(str);
	*i += len + 1;
	tmp = ft_substr(str, 0, len);
	if (!tmp)
		exit(0);
	env_value = _getenv(*env, tmp);
	if (!env_value)
		return (0);
	free(tmp);
	len = ft_strlen(env_value);
	str_insert(new, env_value);
	return (len);
}
