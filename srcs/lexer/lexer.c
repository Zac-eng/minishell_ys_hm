/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 18:40:20 by yususato          #+#    #+#             */
/*   Updated: 2024/06/16 14:55:36 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	lexer_error(t_token *lexer_head, char current);

t_token	*lexer(char *line)
{
	t_token	*lexer;
	t_token	*tmp;
	t_token	*token;

	lexer = NULL;
	while (line && *line != '\0')
	{
		if (split_space(&line, line))
			continue ;
		else if (*line == '<' || *line == '>')
			token = split_red(&line, line);
		else if (*line == '|')
			token = split_pipe(&line, line);
		else if (check_word(line))
			token = split_word(&line, line);
		else
			return (lexer_error(lexer, *line), NULL);
		if (lexer == NULL)
			lexer = token;
		else
			tmp->next = token;
		tmp = token;
	}
	return (lexer);
}

static void	lexer_error(t_token *lexer_head, char current)
{
	free_lexer(lexer_head);
	printf("minishell: syntax error near unexpected token `%c'\n", current);
	g_status = PARSE_ERROR;
}
