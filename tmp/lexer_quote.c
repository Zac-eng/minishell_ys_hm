/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_quote.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:19:28 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/06/16 17:02:04 by hmiyazak         ###   ########.fr       */
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
	i = ft_strlen(token->str);
	new = ft_calloc(i - 2, sizeof(char));
	tmp++;
	i = 0;
	while (tmp[i] != '\'' && tmp[i])
	{
		new[i] = tmp[i];
		i++;
	}
	if (*tmp == '\0')
	{
		free(token->str);
		put_error(PARSE_ERROR, tmp);
	}
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
	i = ft_strlen(token->str);
	new = ft_calloc(i - 2, sizeof(char));
	tmp++;
	i = 0;
	while (tmp[i] != '\"' && tmp[i])
	{
		new[i] = tmp[i];
		i++;
	}
	if (*tmp == '\0')
	{
		free(token->str);
		put_error(PARSE_ERROR, tmp);
	}
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
