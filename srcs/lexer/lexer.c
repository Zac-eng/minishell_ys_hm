/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 18:40:20 by yususato          #+#    #+#             */
/*   Updated: 2024/06/10 19:47:48 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*lexer(char *line)
{
	t_token	*lexer;
	t_token	*tmp;
	t_token	*token;

	lexer = NULL;
	while (*line != '\0' && line)
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
			put_error_exit("need to be editted");
		if (lexer == NULL)
			lexer = token;
		else
			tmp->next = token;
		tmp = token;
	}
	return (lexer);
}
