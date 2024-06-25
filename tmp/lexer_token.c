/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:20:49 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/06/13 11:23:01 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(char *line, t_token_kind kind)
{
	t_token	*token;

	if (line == NULL)
		return (NULL);
	token = ft_calloc(1, sizeof(t_token));
	if (token == NULL)
		return (NULL);
	token->str = line;
	token->kind = kind;
	token->next = NULL;
	return (token);
}
