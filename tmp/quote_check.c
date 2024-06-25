/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 19:59:09 by yususato          #+#    #+#             */
/*   Updated: 2024/06/24 22:11:24 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	after_quote_check(char *line, int first_flag)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (line[i] != ' ' && line[i])
	{
		if (line[i] == '\'')
		{
			return (1);
		}
		else if (line[i] == '\"')
			return (2);
		i++;
	}
	return (0);
}

void	handle_single_quote(char *line, int *i, int *first_flag, int *delete_flag)
{
	if (*first_flag == 0)
	{
		(*i)++;
		*first_flag = 1;
		*delete_flag += 1;
	}
	else if (*first_flag == 1)
	{
		(*i)++;
		*first_flag = 0;
		*delete_flag += 1;
	}
	else if (*first_flag == 2)
	{
		if (after_quote_check(&line[*i], *first_flag) == 1)
		{
			(*i)++;
			while (line[*i] != ' ' && line[*i] && line[*i] != '\'')
				(*i)++;
			if (line[*i] == '\'')
				*delete_flag += 2;
		}
		else
			(*i)++;
	}
}

void	handle_double_quote(char *line, int *i, int *first_flag, int *delete_flag)
{
	if (*first_flag == 0)
	{
		(*i)++;
		*first_flag = 2;
		*delete_flag += 1;
	}
	else if (*first_flag == 2)
	{
		(*i)++;
		*first_flag = 0;
		*delete_flag += 1;
	}
	else if (*first_flag == 1)
	{
		if (after_quote_check(&line[*i], *first_flag) == 1)
		{
			(*i)++;
			while (line[*i] != ' ' && line[*i] && line[*i] != '\'')
				(*i)++;
			if (line[*i] == '\'')
				*delete_flag += 2;
		}
		else
			(*i)++;
	}
}

int	delete_word_check(char *line, int *first_flag, int *i)
{
	int		delete_flag;

	delete_flag = 0;
	while (line[*i] != ' ' && line[*i])
	{
		if (line[*i] == '<' || line[*i] == '>' || line[*i] == '|')
			break ;
		if (line[*i] == '\'')
			handle_single_quote(line, i, first_flag, &delete_flag);
		else if (line[*i] == '\"')
			handle_double_quote(line, i, first_flag, &delete_flag);
		else
			(*i)++;
	}
	return (delete_flag);
}
