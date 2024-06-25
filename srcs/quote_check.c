/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/22 21:30:59 by yususato          #+#    #+#             */
/*   Updated: 2024/06/25 10:19:46 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	squote_check(char *line)
{
	int i;

	i = 1;
	while (line[i] && line[i] != ' ')
	{
		if (line[i] == '\'')
			return (true);
	}
	return (false);
}

bool	dquote_check(char *line)
{
	int i;

	i = 1;
	while (line[i] && line[i] != ' ')
	{
		if (line[i] == '\'')
			return (true);
	}
	return (false);
}

bool	all_quote_check(char *line)
{
	int		i;
	int		s_flag;
	int		d_flag;
	bool	first_flag;
	char	*set;

	i = 0;
	first_flag = 0;
	s_flag = 0;
	d_flag = 0;
	while (line[i] != ' ' && line[i])
	{
		if (line[i] == '\'')
		{
			first_flag = 1;
			break ;
		}
		else if (line[i] == '\"')
		{
		 	first_flag = 2;
			break ;
		}
		i++;
	}
	if (first_flag == 0)
		return (true);
	i = 0;
	while (line[i] != ' ' && line[i])
	{
		if (line[i] == '\'')
		{
			if (!squote_check(&line[i]))
			s_flag++;
		}
		else if (line[i] == '\"')
		{
			if (!dquote_check(&line[i]))
				d_flag++;
		}
		i++;
	}
	if ((first_flag == 1 && s_flag % 2 != 0) || first_flag == 2 && d_flag != 2)
		return (false);
	return (true);
}

bool	after_quote_check(char *line)

t_token	*split_word(char **tmp, char *line)
{
	char	*set;
	int		i;
	int		flag;
	int		first_flag;
	int		delete_flag;
	int		first;
	int		tmp_flag;

	flag = 0;
	first_flag = 0;
	delete_flag = 0;
	first = 0;
	if (*line == '\'')
		return (split_squote(tmp, line));
	else if (*line == '\"')
		return (split_dquote(tmp, line));
	if (!all_quote_check(line, &first_flag))
	{
		set = ft_strdup(line);
		return ((create_token(set, NOT_TK_QUOTE)));
	}
	while (line[i] != ' ' && line[i])
	{
		if (line[i] == '\'' && )
		{
		}
		else if (line[i] == '\"')
		{
			if (first_flag == 2)
			{
				delete_flag = 2;
				first_flag = 0;
			}
			else if (first_flag == 0)
				first_flag = 2;
		}
		if (line[i] == '<' || line[i] == '>' || line[i] == '|')
		{
			i--;
			break;
		}
		i++;
	}
	i = i - delete_flag * 2;
	set = (char *)calloc(sizeof(char), i + 1);
	if (set == NULL)
		return (put_error(PARSE_ERROR, &line[i]), NULL);
	i = 0;
	while (*line != ' ' && *line)
	{
		if (*line == '<' || *line == '>' || *line == '|')
			break ;
		if (*line != '\'' && *line != '\"')
		{
			set[i] = *line;
			i++;
			line++;
		}
		if (*line == '\'')
		{
			if (after_quote_check(line))
				line++;
			else
			{
				set[i] = *line;
				i++;
				line++;
		}
		else if (*line == '\"')
		{
			if (after_quote_check(line))
				line++;
			else
			{
				set[i] = *line;
				i++;
				line++;
			}	
		}
	}
	*tmp = line;
	return (create_token(set, TK_CMD));
}
