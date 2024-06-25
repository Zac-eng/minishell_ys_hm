/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:20:40 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/06/24 22:13:31 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	split_space(char **tmp, char *line)
{
	if (!(*line && (*line == ' ' || *line == '\t' || *line == '\n')))
		return (false);
	while (*line && (*line == ' ' || *line == '\t' || *line == '\n'))
		line++;
	*tmp = line;
	return (true);
}

t_token	*split_pipe(char **tmp, char *line)
{
	char	*set;
	t_token	*token;

	set = strdup("|");
	*tmp = &line[1];
	token = create_token(set, TK_PIPE);
	return (token);
}

t_token	*split_red(char **tmp, char *line)
{
	if (*line == '<')
	{
		*tmp += 1;
		if (line[1] == '<')
		{
			*tmp += 1;
			return (create_token(ft_strdup("<<"), TK_DLESS));
		}
		else
			return (create_token(strdup("<"), TK_LESS));
	}
	else if (*line == '>')
	{
		*tmp += 1;
		if (line[1] == '>')
		{
			*tmp += 1;
			return (create_token(strdup(">>"), TK_DGREAT));
		}
		else
			return (create_token(strdup(">"), TK_GREAT));
	}
	exit(0);
}

t_token	*split_word(char **tmp, char *line)
{
	char	*set;
	int		i;
	int		first_flag;
	int		delete_flag;
	int		first;
	int		keep_flag;

	i = 0;
	first = 0;
	first_flag = 0;
	delete_flag = 0;
	// if (*line == '\'')
	// 	return (split_squote(tmp, line));
	// else if (*line == '\"')
	// 	return (split_dquote(tmp, line));
	delete_flag = delete_word_check(line, &first_flag, &i);
	i = i - delete_flag;
	set = (char *)calloc(sizeof(char), i + 1);
	if (set == NULL)
		return (put_error(PARSE_ERROR, &line[i]), NULL);
	i = 0;
	line = quote_set(line, set, &first_flag, &first);
	*tmp = line;
	if (first_flag != 0)
		return (create_token(set, NOT_TK_QUOTE));
	return (create_token(set, TK_CMD));
}
