/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:20:40 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/06/24 13:41:05 by yususato         ###   ########.fr       */
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

bool	all_quote_check(char *line, int *first_flag)
{
	int		i;

	i = 0;
	while (line[i] != ' ' && line[i])
	{
		if (line[i] == '\'')
		{
			*first_flag = 1;
			break ;
		}
		else if (line[i] == '\"')
		{
		 	*first_flag = 2;
			break ;
		}
		i++;
	}
	if (*first_flag == 0)
		return (true);
	i = 0;
	while (line[i] != ' ' && line[i])
	{
		if (line[i] == '\'')
		{
			if (*first_flag == 1)
				*first_flag = 0;
			else if (*first_flag == 0)
				*first_flag = 1;
		}
		else if (line[i] == '\"')
		{
			if (*first_flag == 2)
				*first_flag = 0;
			else if (*first_flag == 0)
				*first_flag = 2;
		}
		i++;
	}
	if (*first_flag == 0)
		return (true);
	return (true);
}

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
			line++;
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
			line++;
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
	int	delete_flag;

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

t_token	*split_word(char **tmp, char *line)
{
	char	*set;
	int		i;
	int		first_flag;
	int		delete_flag;
	int		first;

	i = 0;
	first = 0;
	first_flag = 0;
	delete_flag = 0;
	if (*line == '\'')
		return (split_squote(tmp, line));
	else if (*line == '\"')
		return (split_dquote(tmp, line));
	delete_flag = delete_word_check(line, &first_flag, &i);
	i = i - delete_flag;
	set = (char *)calloc(sizeof(char), i + 1);
	if (set == NULL)
		return (put_error(PARSE_ERROR, &line[i]), NULL);
	i = 0;
	line = quote_set(line, set, &first_flag, &first);
	*tmp = line;
	return (create_token(set, TK_CMD));
}
