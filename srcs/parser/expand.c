/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:50:15 by yususato          #+#    #+#             */
/*   Updated: 2024/07/07 16:35:21 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	expand_cmd(t_token *tmp, t_env **env)
{
	int		i;
	int		len;
	char	*set;

	i = 0;
	len = 0;
	len = cmd_len(tmp->str, env);
	set = env_insert(tmp->str, env, len);
	free(tmp->str);
	tmp->str = set;
}

void	expand_dquote(t_token *tmp, t_env **env)
{
	int		len;
	char	*set;

	len = 0;
	len = cmd_len(tmp->str, env);
	set = env_insert(tmp->str, env, len);
	free(tmp->str);
	tmp->str = set;
}

void	expand(t_token *lexer, t_env **env)
{
	t_token	*tmp;

	tmp = lexer;
	while (tmp != NULL)
	{
		if (tmp->kind == TK_CMD)
			expand_cmd(tmp, env);
		else if (tmp->kind == TK_DQUOTE)
			expand_dquote(tmp, env);
		tmp = tmp->next;
	}
}
