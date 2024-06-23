/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 19:54:01 by yususato          #+#    #+#             */
/*   Updated: 2024/06/23 21:45:52 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	(*parser_tmp)->cmd[0] = ft_itoa(g_status);
	if ((*parser_tmp)->cmd[0] == NULL)
		return (false);
	return (true);
}

int	env_question_add(char *str, t_env **env, char *new, int *i)
{
	int		len;
	char	*tmp;

	tmp = ft_itoa(g_status);
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
	len = is_space(str);
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

int	question_add_len(char *str, t_env **env, int *i)
{
	int		len;
	char	*tmp;

	tmp = ft_itoa(g_status);
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
	len = is_space(str);
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