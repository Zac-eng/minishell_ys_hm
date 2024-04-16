/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 11:50:45 by yususato          #+#    #+#             */
/*   Updated: 2024/02/14 14:54:50 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_squote(t_token *token)
{
	char	*new;
	char	*tmp;
	int		i;

	if (token->str[0] != '\'' || token == NULL)
		return ;
	tmp = token->str;
	i = strlen(token->str);
	new = calloc(i-2, sizeof(char));
	tmp++;
	i = 0;
	while (tmp[i]  != '\'' && tmp[i])
	{
		new[i] = tmp[i];
		i++;
	}

	if (*tmp == '\0')
		ft_error();	free(token->str);
	token->str = new;
	return ;
}

void	remove_dquote(t_token *token)
{
	char	*new;
	char	*tmp;
	int		i;

	if (token->str[0] != '\"' || token == NULL)
		return ;
	tmp = token->str;
	i = strlen(token->str);
	new = calloc(i-2, sizeof(char));
	tmp++;
	i = 0;
	while (tmp[i]  != '\"' && tmp[i])
	{
		new[i] = tmp[i];
		i++;
	}

	if (*tmp == '\0')
		ft_error();	free(token->str);
	token->str = new;
	return ;
}

void	expand(t_token *token)
{
	while (token->next != NULL)
	{
		if (token->str[0] == '\'')
			remove_squote(token);
		else if (token->str[0] == '\"')
			remove_dquote(token);
		token = token->next;
	}
}