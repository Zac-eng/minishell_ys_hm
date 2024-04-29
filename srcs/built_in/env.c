/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 09:55:42 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/04/29 12:01:30 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_env(char **env)
{
	int	iter;

	iter = 0;
	if (env == NULL)
		return ;
	while (env[iter] != NULL)
	{
		printf("%s\n", env[iter]);
		iter++;
	}
}
