/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:17:01 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/06/25 23:35:10 by yususato         ###   ########.fr       */
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

void	expand(t_token *tmp, t_env **env)
{
	int	len;

	len = 0;
	len = ft_strlen(tmp->str);
	if (tmp->kind == TK_CMD)
		expand_cmd(tmp, env);
	else if (tmp->kind == TK_SQUOTE)
		return ;
	else if (tmp->kind == TK_DQUOTE)
		expand_dquote(tmp, env);
}

bool	start_check(t_token *tmp, t_env **env)
{
	if (tmp->kind == TK_CMD || tmp->kind == TK_SQUOTE || tmp->kind == TK_DQUOTE)
	{
		expand(tmp, env);
		return (true);
	}
	return (false);
}

bool	connect_check(t_token *tmp, t_env **env)
{
	if (tmp->kind == TK_CMD || tmp->kind == TK_SQUOTE || tmp->kind == TK_DQUOTE)
	{
		return (true);
	}
	return (false);
}

void	node_delete(t_token *tmp, t_token *tmp_next)
{
	t_token	*tmp2;

	tmp2 = tmp_next->next;
	tmp->next = tmp2;
	free(tmp_next->str);
	free(tmp_next);
}

void	token_check(t_token	*lexer, t_env **env)
{
	t_token	*tmp;
	t_token	*tmp2;
	bool	flag;
	char	*new;

	tmp = lexer;
	tmp2 = lexer;
	flag = true;
	while (tmp->next != NULL && tmp != NULL)
	{
		if (tmp->space_flag == false)
		{
			if (start_check(tmp, env) && connect_check(tmp->next, env))
			{
				new = ft_strjoin(tmp->str, tmp->next->str);
				free(tmp->str);
				tmp->str = new;
				node_delete(tmp, tmp->next);
			printf("parser:%s,next%s\n",tmp->str,tmp->next->str);
			}
		}
		else
		{
		printf("yuppponnnn\n");
			tmp = tmp->next;
		}
	}
}
