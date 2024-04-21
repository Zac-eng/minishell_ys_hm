/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/27 18:40:20 by yususato          #+#    #+#             */
/*   Updated: 2024/04/21 16:08:03 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// t_token	*lexer(char *line)
// {
// 	t_token	*lexer;
// 	t_token	*tmp;
// 	t_token	*token;

// 	lexer = NULL;
// 	while (*line != '\0' && line)
// 	{
// 		if (split_space(&line, line))
// 			continue ;
// 		else if (*line == '<' || *line == '>')
// 			token = split_red(&line, line);
// 		else if (*line == '|')
// 			token = split_pipe(&line, line);
// 		else if (check_word(line))
// 			token = split_word(&line, line);
// 		else
// 			ft_error();
// 		if (lexer == NULL)
// 			lexer = token;
// 		else
// 			tmp->next = token;
// 		tmp = token;
// 	}
// 	tmp = lexer;
// 	for(int i = 0;tmp != NULL; ++i){
// 		printf("%d :%s\n", i, tmp->str);
// 		tmp = tmp->next;
// 	}
// 	return (lexer);
// }

// t_token	*create_token(char *line, t_token_kind kind)
// {
// 	t_token	*token;

// 	token = calloc(1, sizeof(*token));
// 	if (token == NULL)
// 		return (NULL);
// 	token->str = line;
// 	token->kind = kind;
// 	token->next = NULL;
// 	return (token);
// }

// bool	split_space(char **tmp, char *line)
// {
// 	if (!(*line && (*line == ' ' || *line == '\t' || *line == '\n')))
// 		return (false);
// 	while (*line && (*line == ' ' || *line == '\t' || *line == '\n'))
// 		line++;
// 	*tmp = line;
// 	return (true);
// }

// t_token	*split_pipe(char **tmp, char *line)
// {
// 	char	*set;
// 	t_token	*token;

// 	set = strdup("|");
// 	*tmp = &line[1];
// 	token = create_token(set, TK_PIPE);
// 	return (token);
// }

// t_token	*split_red(char **tmp, char *line)
// {
// 	char	*set;
// 	t_token	*token;

// 	if (*line == '<')
// 	{
// 		if (line[1] == '<')
// 		{
// 			set = strdup("<<");
// 			*tmp = &line[2];
// 			return (create_token(set, TK_DLESS));
// 		}
// 		else
// 		{
// 			set = strdup("<");
// 			*tmp = &line[1];
// 			return (create_token(set, TK_LESS));
// 		}
// 	}
// 	else if (*line == '>')
// 	{
// 		if (line[1] == '>')
// 		{
// 			set = strdup(">>");
// 			*tmp = &line[2];
// 			return (create_token(set, TK_DGREAT));
// 		}
// 		else
// 		{
// 			set = strdup(">");
// 			*tmp = &line[1];
// 			return (create_token(set, TK_GREAT));
// 		}
// 	}
// 	exit(0);
// }

// t_token	*split_squote(char **tmp, char *line)
// {
// 	int		i;
// 	int		a;
// 	char	*set;

// 	i = 1;
// 	a = 0;
// 	i++;
// 	while (line[i])
// 	{
// 		if (line[i] == '\'')
// 		{
// 			i++;
// 			break ;
// 		}
// 		i++;
// 	}
// 	set = (char *)malloc(sizeof(char) * (i + 1));
// 	while (a <= i)
// 	{
// 		set[a] = *line;
// 		a++;
// 		line++;
// 	}
// 	set[a] = '\0';
// 	*tmp = line;
// 	return (create_token(set, TK_SQUOTE));
// }

// t_token	*split_dquote(char **tmp, char *line)
// {
// 	int		i;
// 	int		a;
// 	char	*set;

// 	i = 1;
// 	a = 0;
// 	while (line[i])
// 	{
// 		if (line[i] == '\"')
// 		{
// 			i++;
// 			break ;
// 		}
// 		i++;
// 	}
// 	set = (char *)malloc(sizeof(char) * (i + 1));
// 	while (a <= i)
// 	{
// 		set[a] = *line;
// 		a++;
// 		line++;
// 	}
// 	set[a] = '\0';
// 	*tmp = line;
// 	return (create_token(set, TK_DQUOTE));
// }

// t_token	*split_word(char **tmp, char *line)
// {
// 	char	*set;
// 	t_token	*token;
// 	int		i;
// 	int		a;

// 	if (*line == '\'')
// 	{
// 		return (split_squote(tmp, line));
// 	}
// 	else if (*line == '\"')
// 	{
// 		return (split_dquote(tmp, line));
// 	}
// 	i = 0;
// 	while (line[i] != ' ' && line[i])
// 		i++;
// 	set = (char *)calloc(sizeof(char), i + 1);
// 	i = 0;
// 	while (line[i] != ' ' && line[i])
// 	{
// 		set[i] = line[i];
// 		i++;
// 	}
// 	*tmp = &line[i];
// 	return (create_token(set, TK_CMD));
// }

// bool	check_word(char	*line)
// {
// 	return (*line && !strchr("|&;()\t\n",*line));
// }

// void	ft_error(void)
// {
// 	printf("Error\n");
// 	exit(0);
// }
