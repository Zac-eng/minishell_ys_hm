/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 18:40:20 by yususato          #+#    #+#             */
/*   Updated: 2024/02/08 12:20:51 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*split_squote(t_stack *lexer, char *line)
{
	int		i;
	int		a;
	char	*set;

	i = 1;
	a = 0;
	while (line[i] && line[i])
	{
		if (line[i] == '\'')
			break ;
		i++;
	}
	set = (char *)malloc(sizeof(char) * (i + 1));
	while (a < i)
	{
		set[a] = line[a];
		a++;
	}
	set[a] = '\0';
	push(lexer, set, S_QUOTE);
	return (&line[i]);
}

char	*split_dquote(t_stack *lexer, char *line)
{
	int		i;
	int		a;
	char	*set;

	i = 1;
	a = 0;
	while (line[i])
	{
		if (line[i] == '\"' && line[i])
			break ;
		i++;
	}
	set = (char *)malloc(sizeof(char) * (i + 1));
	while (a < i)
	{
		set[a] = line[a];
		a++;
	}
	set[a] = '\0';
	push(lexer, set, D_QUOTE);
	return (&line[i]);
}

char	*split_space(t_stack *lexer, char *line)
{
	int		i;
	int		a;
	char	*set;

	i = 1;
	a = 0;
	while (line[i] != ' ' && line[i])
	{
		i++;
	}
	set = (char *)calloc(sizeof(char), i);
	i = 1;
	while (line[i] != ' ' && line[i])
	{
		set[a] = line[i];
		a++;
		i++;
	}
	push(lexer, set, SPASE);
	return (&line[i]);
}

char	*split_line(t_stack *lexer, char *line)
{
	char	*set;

	set = (char *)malloc(sizeof(char) * 2);
	set[0] = line[0];
	set[1] = '\0';
	push(lexer, set, PIPE);
	line++;
	return (line);
}

char	*split_str(t_stack *lexer, char *line)
{
	int		i;
	int		a;
	char	*set;

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
	push(lexer, set, STR);
	return (&line[i]);
}

t_stack	lexer(char *line)
{
	int		i;
	t_stack	*lexer;

	i = 0;
	lexer = create_stack();
	while (*line != '\0' && line)
	{
		if (*line == '\'')
			line = split_squote(lexer, line);
		else if (*line == '\"')
			line = split_dquote(lexer, line);
		else if (*line == '<' || *line == '>')
			line = split_line(lexer, line);
		else if (*line == '|')
			line = split_line(lexer, line);
		else if (*line == ' ')
			line = split_space(lexer, line);
		else if (ft_isalpha(*line))
			line = split_str(lexer, line);
		else
			line++;
	}
	return (*lexer);
}