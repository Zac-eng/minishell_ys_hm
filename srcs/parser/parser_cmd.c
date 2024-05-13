/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 18:12:18 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/05/13 18:38:52 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	cmd_init(t_token **lexer_tmp, t_parser **parser_tmp)
{
	(*parser_tmp)->cmd = (char **)calloc(sizeof(char *) * 2);
	if ((*parser_tmp)->cmd == NULL)
		ft_exit();
	(*parser_tmp)->cmd[0] = strdup((*lexer_tmp)->str);
	if ((*parser_tmp)->cmd[0] == NULL)
		ft_exit();
	(*tmp)->cmd[1] = NULL;
	return ;
}

void	cmd_add(t_token **lexer_tmp, t_parser **parser_tmp, char **tmp)
{
	int	i;

	i = 0;
	while ((*parser_tmp)->cmd[i] != NULL)
	{
		tmp[i] = strdup((*parser_tmp)->cmd[i]);
		i++;
	}
	tmp[i] = strdup((*lexer_tmp)->str);
	tmp[i+1] = NULL;
	free_parser_tmp((*parser_tmp)->cmd)
	(*parser_tmp)->cmd = (char **)calloc(sizeof(char*) * (i + 2));
	i = 0;
	while (tmp[i] != NULL)
	{
		(*parser_tmp)->cmd[i] = strdup(tmp[i]);
		i++;
	}
	(*parser_tmp)->cmd[i] = NULL;
	free(tmp);
}

void	*parser_cmd(t_token **lexer_tmp, t_parser **parser_tmp)
{
	char	**tmp;
	int		i;

	i = 0;
	if ((*parser_tmp)->cmd == NULL)
	{
		cmd_init(lexer_tmp, parser_tmp);
	}
	else
	{
		while ((*parser_tmp)->cmd[i] != NULL)
			i++;
		tmp = (char **)calloc(sizeof(char *) * (i + 2));
		cmd_add(lexer_tmp, parser_tmp, tmp);
	}
	return (parser_tmp);
}