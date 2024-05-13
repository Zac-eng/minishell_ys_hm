/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:20:40 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/05/13 18:20:41 by hmiyazak         ###   ########.fr       */
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
	char	*set;
	t_token	*token;

	if (*line == '<')
	{
		if (line[1] == '<')
		{
			set = strdup("<<");
			*tmp = &line[2];
			return (create_token(set, TK_DLESS));
		}
		else
		{
			set = strdup("<");
			*tmp = &line[1];
			return (create_token(set, TK_LESS));
		}
	}
	else if (*line == '>')
	{
		if (line[1] == '>')
		{
			set = strdup(">>");
			*tmp = &line[2];
			return (create_token(set, TK_DGREAT));
		}
		else
		{
			set = strdup(">");
			*tmp = &line[1];
			return (create_token(set, TK_GREAT));
		}
	}
	exit(0);
}

t_token	*split_squote(char **tmp, char *line)
{
	int		i;
	int		a;
	char	*set;

	i = 1;
	a = 0;
	i++;
	while (line[i])
	{
		if (line[i] == '\'')
		{
			i++;
			break ;
		}
		i++;
	}
	set = (char *)malloc(sizeof(char) * (i + 1));
	while (a <= i)
	{
		set[a] = *line;
		a++;
		line++;
	}
	set[a] = '\0';
	*tmp = line;
	return (create_token(set, TK_SQUOTE));
}

t_token	*split_dquote(char **tmp, char *line)
{
	int		i;
	int		a;
	char	*set;

	i = 1;
	a = 0;
	while (line[i])
	{
		if (line[i] == '\"')
		{
			i++;
			break ;
		}
		i++;
	}
	set = (char *)malloc(sizeof(char) * (i + 1));
	while (a <= i)
	{
		set[a] = *line;
		a++;
		line++;
	}
	set[a] = '\0';
	*tmp = line;
	return (create_token(set, TK_DQUOTE));
}

t_token	*split_word(char **tmp, char *line)
{
	char	*set;
	t_token	*token;
	int		i;
	int		a;

	if (*line == '\'')
	{
		return (split_squote(tmp, line));
	}
	else if (*line == '\"')
	{
		return (split_dquote(tmp, line));
	}
	i = 0;
	while (line[i] != ' ' && line[i])
		i++;
	set = (char *)calloc(sizeof(char), i + 1);
	i = 0;
	while (line[i] != ' ' && line[i])
	{
		set[i] = line[i];
		i++;
	}
	*tmp = &line[i];
	return (create_token(set, TK_CMD));
}