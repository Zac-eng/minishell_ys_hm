/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:20:40 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/06/13 11:37:14 by hmiyazak         ###   ########.fr       */
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

	if (*line == '\'')
		return (split_squote(tmp, line));
	else if (*line == '\"')
		return (split_dquote(tmp, line));
	i = 0;
	while (line[i] != ' ' && line[i])
		i++;
	set = (char *)calloc(sizeof(char), i + 1);
	if (set == NULL)
		put_error_exit("need to be editted");
	i = 0;
	while (line[i] != ' ' && line[i])
	{
		set[i] = line[i];
		i++;
	}
	*tmp = &line[i];
	return (create_token(set, TK_CMD));
}
