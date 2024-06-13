/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split_quote.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 11:12:37 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/06/13 21:23:13 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*split_squote(char **tmp, char *line)
{
	int		start;
	int		end;
	char	*set;

	start = 0;
	end = 0;
	printf("%s\n", line);
	while (line[start])
	{
		if (line[start] == '\'')
			break ;
		start++;
	}
	set = (char *)malloc(sizeof(char) * (start + 1));
	if (set == NULL)
		put_error_exit("need to be editted");
	end = start;
	start = 0;
	line++;
	while (start <= end && *line)
	{
		if (*line == '\'')
			break ;
		set[start] = *line;
		start++;
		line++;
	}
	set[end] = '\0';
	*tmp = line;
	return (create_token(set, TK_SQUOTE));
}

t_token	*split_dquote(char **tmp, char *line)
{
	int		start;
	int		end;
	char	*set;

	start = 1;
	end = 0;
	while (line[start])
	{
		if (line[start] == '\"')
			break ;
		start++;
	}
	set = (char *)malloc(sizeof(char) * (start));
	if (set == NULL)
		put_error_exit("need to be editted");
	end = start;
	start = 0;
	line++;
	while (start <= end && *line)
	{
		if (*line == '\"')
			break ;
		set[start] = *line;
		start++;
		line++;
	}
	set[end] = '\0';
	*tmp = line;
	return (create_token(set, TK_DQUOTE));
}

