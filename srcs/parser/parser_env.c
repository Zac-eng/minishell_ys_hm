/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:54:01 by yususato          #+#    #+#             */
/*   Updated: 2024/07/02 18:44:03 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	question_add_len(char *str, t_env **env, int *i)
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
	t_env	*head_env;
	int		len;
	char	*tmp;

	len = 0;
	len = is_squote_space(str);
	*i += len + 1;
	tmp = ft_substr(str, 0, len);
	if (!tmp)
		exit(0);
	head_env = find_node(*env, tmp);
	if (!head_env)
		return (0);
	free(tmp);
	len = ft_strlen(head_env->value);
	// free(head_env);
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
				tmp = question_add_len(&str[i+1], env, &i);
				count += tmp;
			}
			else
			{
				tmp = env_add_len(&str[i+1], env, &i);
				count += tmp;
			}
		}
		else
		{
			i++;
			count++;
		}
	}
	return (count);
}

bool	parser_env_init(t_token **lexer_tmp, t_parser **parser_tmp, t_env **env)
{
	t_env	*head_env;

	head_env = find_node(*env, (&(*lexer_tmp)->str[1]));
	if (!head_env)
		return (false);
	(*parser_tmp)->cmd[0] = strdup(head_env->value);
	return (true);
}

bool	env_question_init(t_token **lexer_tmp, t_parser **parser_tmp, t_env **env)
{
	(*parser_tmp)->cmd[0] = ft_itoa(g_flag);
	if ((*parser_tmp)->cmd[0] == NULL)
		return (false);
	return (true);
}

int	env_question_add(char *str, t_env **env, char *new, int *i)
{
	int		len;
	char	*tmp;

	tmp = ft_itoa(g_flag);
	len = ft_strlen(tmp);
	*i += 2;
	str_insert(new, tmp);
	free(tmp);
	return (len);
}

int	parser_env_add(char *str, t_env **env, char *new, int *i)
{
	t_env	*head_env;
	int		len;
	char	*tmp;

	len = 0;
	len = is_squote_space(str);
	*i += len + 1;
	tmp = ft_substr(str, 0, len);
	if (!tmp)
		exit(0);
	head_env = find_node(*env, tmp);
	if (!head_env)
		return (0);
	free(tmp);
	len = ft_strlen(head_env->value);
	str_insert(new, head_env->value);
	// free(head_env);
	return (len);
}

char	*env_insert(char *str, t_env **env, int len)
{
	int		i;
	int		tmp;
	int		count;
	char	*new;

	i = 0;
	count = 0;
	new = (char *)malloc(sizeof(char) * (len + 1));
	while (str[i])
	{
		if (str[i] == '$')
		{
			if (str[i + 1] && str[i + 1] == '?')
			{
				tmp = env_question_add(&str[i+1], env, &new[count], &i);
				count += tmp;
			}
			else if (str[i + 1] == '\0' || str[i + 1] == ' ' || str[i + 1] == '$')
			{
				new[count] = str[i];
				i++;
				count++;
			}
			else
			{
				tmp = parser_env_add(&str[i+1], env, &new[count], &i);
				count += tmp;
			}
		}
		else
		{
			new[count] = str[i];
			i++;
			count++;
		}
	}
	new[count] = '\0';
	return (new);
}
