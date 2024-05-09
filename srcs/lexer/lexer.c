/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 18:40:20 by yususato          #+#    #+#             */
/*   Updated: 2024/04/21 16:08:03 by hmiyazak         ###   ########.fr       */
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
			ft_error();
		if (lexer == NULL)
			lexer = token;
		else
			tmp->next = token;
		tmp = token;
	}
	tmp = lexer;
	for(int i = 0;tmp != NULL; ++i){
		printf("%d :%s\n", i, tmp->str);
		tmp = tmp->next;
	}
	return (lexer);
}
