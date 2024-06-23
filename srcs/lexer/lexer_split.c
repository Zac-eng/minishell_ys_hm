/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_split.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:20:40 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/06/22 22:54:18 by yususato         ###   ########.fr       */
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
			printf("bb\n");
			return (1);
		}
		else if (line[i] == '\"')
			return (2);
		i++;
	}
	return (0);
}

t_token	*split_word(char **tmp, char *line)
{
	char	*set;
	int		i;
	int		flag;
	int		first_flag;
	int		delete_flag;
	int		tmp_flag;
	int		first;

	flag = 0;
	first = 0;
	first_flag = 0;
	delete_flag = 0;
	tmp_flag = 0;
	if (*line == '\'')
		return (split_squote(tmp, line));
	else if (*line == '\"')
		return (split_dquote(tmp, line));
	all_quote_check(line, &first_flag);
	tmp_flag = first_flag;
	first_flag = 0;
	while (line[i] != ' ' && line[i])
	{

		if (line[i] == '<' || line[i] == '>' || line[i] == '|')
			break ;
		if (line[i] == '\'')
		{
			if (first_flag == 0)
			{
				i++;
				first_flag = 1;
				delete_flag += 1;
			}
			else if (first_flag == 1)
			{
				i++;
				first_flag = 0;
				delete_flag += 1;
			}
			else if (first_flag == 2)
			{
				printf("first%d\n",first_flag);
				if (after_quote_check(&line[i], first_flag) == 1)
				{
					line++;
					while (line[i] != ' ' && line[i] && line[i] != '\'')
					{
						i++;
					}
					if (line[i] == '\'')
						delete_flag += 2;
				}
				else
					i++;
			}
		}
		else if (line[i] == '\"')
		{
			if (first_flag == 0)
			{
				i++;
				first_flag = 2;
				delete_flag += 1;
			}
			else if (first_flag == 2)
			{
				i++;
				first_flag = 0;
				delete_flag += 1;
			}
			else if (first_flag == 1)
			{
				if (after_quote_check(&line[i], first_flag) == 1)
				{

					i++;
				}
				else
				{
					i++;
					while (line[i] != ' ' && line[i] && line[i] != '\'')
					{
						i++;
					}
					if (line[i] == '\'')
						delete_flag += 2;
				}
			}
			}
		else
			i++;
	}
	i = i -  delete_flag;
	printf("del%d\n",i);
	set = (char *)calloc(sizeof(char), i + 1);
	if (set == NULL)
		return (put_error(PARSE_ERROR, &line[i]), NULL);
	i = 0;
	while (*line != ' ' && *line)
	{
		if (*line == '<' || *line == '>' || *line == '|')
			break ;
		if (*line == '\'' && *line == '\'' && first == 0)
		{
			line++;
		}
		if (*line == '\'')
		{
			if (first_flag == 0)
			{
				line++;
				first_flag = 1;
			}
			else if (first_flag == 1)
			{
				line++;
				first_flag = 0;
			}
			else if (first_flag == 2)
			{
				if (after_quote_check(line, first_flag) == 1)
				{
					printf("aa\n");
					set[i] = *line;
					i++;
					line++;
				}
				else
				{
					line++;
					while (*line != ' ' && *line && *line != '\'')
					{
						set[i] = *line;
						i++;
						line++;
					}
					if (*line == '\'')
						line++;
				}
			}
		}
		else if (*line == '\"')
		{
			
			if (first_flag == 0)
			{
				line++;
				first_flag = 2;
			}
			else if (first_flag == 2)
			{
				line++;
				first_flag = 0;
			}
			else if (first_flag == 1)
			{
				if (after_quote_check(line, first_flag) == 2)
				{
					set[i] = *line;
					i++;
					line++;
				}
				else
				{
					line++;
					while (*line != ' ' && *line && *line != '\'')
					{
						set[i] = *line;
						i++;
						line++;
					}
					if (*line == '\'')
						line++;
				}
			}
		}
		else
		{
			set[i] = *line;
			i++;
			line++;
		}
	}
	
	printf("set:%s\n",set);
	printf("line:%s\n",line);
	exit(0);
	*tmp = line;
	return (create_token(set, TK_CMD));
}
