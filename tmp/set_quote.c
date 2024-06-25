/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_quote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:56:57 by yususato          #+#    #+#             */
/*   Updated: 2024/06/24 19:57:30 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_single_quote(char **line, char *set, int *first_flag, int *i)
{
	if (*first_flag == 0)
	{
		(*line)++;
		*first_flag = 1;
	}
	else if (*first_flag == 1)
	{
		(*line)++;
		*first_flag = 0;
	}
	else if (*first_flag == 2)
	{
		if (after_quote_check(*line, *first_flag) == 1)
		{
			set[*i] = **line;
			(*i)++;
			(*line)++;
		}
		else
		{
			(*line)++;
			while (**line != ' ' && **line && **line != '\'')
			{
				set[*i] = **line;
				(*i)++;
				(*line)++;
			}
			if (**line == '\'')
				(*line)++;
		}
	}
}

void	set_double_quote(char **line, char *set, int *first_flag, int *i)
{
	if (*first_flag == 0)
	{
		(*line)++;
		*first_flag = 2;
	}
	else if (*first_flag == 2)
	{
		(*line)++;
		*first_flag = 0;
	}
	else if (*first_flag == 1)
	{
		if (after_quote_check(*line, *first_flag) == 2)
		{
			set[*i] = **line;
			(*i)++;
			(*line)++;
		}
		else
		{
			(*line)++;
			while (**line != ' ' && **line && **line != '\'')
			{
				set[*i] = **line;
				(*i)++;
				(*line)++;
			}
			if (**line == '\'')
				(*line)++;
		}
	}
}

char	*quote_set(char *line, char *set, int *first_flag, int *first)
{
	int		i;

	i = 0;
	while (*line != ' ' && *line)
	{
		if (*line == '<' || *line == '>' || *line == '|')
			break ;
		if (*line == '\'' && *line == '\'' && first == 0)
		{
			line++;
			continue ;
		}
		if (*line == '\'')
			set_single_quote(&line, set, first_flag, &i);
		else if (*line == '\"')
			set_double_quote(&line, set, first_flag, &i);
		else
		{
			set[i] = *line;
			i++;
			line++;
		}
	}
	return (line);
}
