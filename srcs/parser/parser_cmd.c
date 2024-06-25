/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:12:18 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/06/25 09:04:22 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	cmd_init(t_token **lexer_tmp, t_parser **parser_tmp, t_env **env)
{
	int		len;

	len = 0;
	(*parser_tmp)->cmd = (char **)calloc(2, sizeof(char *));
	if ((*parser_tmp)->cmd == NULL)
		exit(0);
	len = cmd_len((*lexer_tmp)->str, env);
	(*parser_tmp)->cmd[0] = env_insert((*lexer_tmp)->str, env, len);
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
	int	len;

	i = 0;
	len = 0;
	while ((*parser_tmp)->cmd[i] != NULL)
	{
		tmp[i] = strdup((*parser_tmp)->cmd[i]);
		i++;
	}
	len = cmd_len((*lexer_tmp)->str, env);
	tmp[i] = env_insert((*lexer_tmp)->str, env, len);
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
	return (new);
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
