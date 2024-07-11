/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 20:04:19 by yususato          #+#    #+#             */
/*   Updated: 2024/07/11 13:14:51 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_special_space(char *str)
{
	int	len;

	len = 0;
	while (str[len] && ft_isalnum(str[len]))
		len++;
	return (len);
}

void	str_insert(char	*new, char *str)
{
	int	len;

	len = 0;
	while (str[len])
	{
		new[len] = str[len];
		len++;
	}
	return ;
}

void	simple_counter(int *i, int *count)
{
	(*i)++;
	(*count)++;
}

void	simple_insert(char *new, char c, int *count, int *i)
{
	new[*count] = c;
	(*count)++;
	(*i)++;
}
