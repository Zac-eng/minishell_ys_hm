/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/25 16:50:15 by yususato          #+#    #+#             */
/*   Updated: 2024/06/25 16:57:18 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_expand(t_token *tmp)
{
	
}

void	expand_cmd(t_token *tmp)
{
	int	i;

	i = 0;
	while (tmp->str[i])
	{
		if (tmp->str[i] == '$')
			env_expand(tmp);
	}
}