/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:12:18 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/06/16 17:18:15 by yususato         ###   ########.fr       */
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

bool	parser_env_add(t_token **lexer_tmp, char **tmp, t_env **env, int i)
{
	t_env	*head_env;

	head_env = find_node(*env, (&(*lexer_tmp)->str[1]));
	if (!head_env)
		return (false);
	tmp[i] = strdup(head_env->value);
	return (true);
}

void	cmd_init(t_token **lexer_tmp, t_parser **parser_tmp, t_env **env)
{
	bool	flag;

	flag = false;
	(*parser_tmp)->cmd = (char **)calloc(2, sizeof(char *));
	if ((*parser_tmp)->cmd == NULL)
		exit(0);
	if ((*lexer_tmp)->str[0] == '$')
	{
		if (parser_env_init(lexer_tmp, parser_tmp, env))
			flag = true;
		else
			flag = false;
	}
	if (flag == false)
		(*parser_tmp)->cmd[0] = strdup((*lexer_tmp)->str);
	if ((*parser_tmp)->cmd[0] == NULL)
		exit(0);
	(*parser_tmp)->cmd[1] = NULL;
	return ;
}

void	free_parser_tmp(t_parser **tmp)
{
	int	i;

	i = 0;
	while ((*tmp)->cmd[i] != NULL)
	{
		free((*tmp)->cmd[i]);
		i++;
	}
	free((*tmp)->cmd);
	return ;
}

void	cmd_add(t_token **lexer_tmp, t_parser **parser_tmp, char **tmp, t_env **env)
{
	int	i;
	int	flag;

	i = 0;
	flag = false;
	while ((*parser_tmp)->cmd[i] != NULL)
	{
		tmp[i] = strdup((*parser_tmp)->cmd[i]);
		i++;
	}
	if ((*lexer_tmp)->str[0] == '$')
	{
		if (parser_env_add(lexer_tmp, tmp, env, i))
			flag = true;
		else
			flag = false;
	}
	if (flag == false)
		tmp[i] = strdup((*lexer_tmp)->str);
	free_parser_tmp(parser_tmp);
	(*parser_tmp)->cmd = (char **)calloc((i + 2), sizeof(char *));
	i = 0;
	while (tmp[i] != NULL)
	{
		(*parser_tmp)->cmd[i] = strdup(tmp[i]);
		i++;
	}
	(*parser_tmp)->cmd[i] = NULL;
	free(tmp);
}

void	*parser_cmd(t_token **lexer_tmp, t_parser **parser_tmp, t_env **env)
{
	char	**tmp;
	int		i;

	i = 0;
	if ((*parser_tmp)->cmd == NULL)
		cmd_init(lexer_tmp, parser_tmp, env);
	else
	{
		while ((*parser_tmp)->cmd[i] != NULL)
			i++;
		tmp = (char **)ft_calloc((i + 2), sizeof(char *));
		cmd_add(lexer_tmp, parser_tmp, tmp, env);
	}
	return (parser_tmp);
}
