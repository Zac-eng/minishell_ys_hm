/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 18:40:20 by yususato          #+#    #+#             */
/*   Updated: 2024/06/25 17:30:38 by yususato         ###   ########.fr       */
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
	while (lexer != NULL)
	{
		printf("lexer:%s\n",lexer->str);
		lexer = lexer->next;
	}
	return (lexer);
}

static void	lexer_error(t_token *lexer_head, char current)
{
	free_lexer(lexer_head);
	put_error(PARSE_ERROR, &current);
}
