/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 09:56:06 by yususato          #+#    #+#             */
/*   Updated: 2024/02/20 16:47:06 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_cmd(t_token *token)
{
	int		i;
	int		len;
	char	*line;

	len = strlen(token->str);
	line = calloc(len + 1, sizeof(char));
	while (token->str[i])
	{
		line[i] = token->str[i]
		i++;
	}
	check_echo(line);
	check_cd(line);
	check_pwd(line);
	check_export(line);
	check_unset(line);
	check_env(line);
	check_exit(line);
	return ;
}

void	parser(t_token *token)
{
	if (token->kind != TK_CMD)
		ft_error();
	else
		check_cmd(token);
	token = token->next;
	while (token->kind != EOF)
	{
		if (token->kin)
	}
	
	
}
