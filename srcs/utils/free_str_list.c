/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_str_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/13 08:58:04 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/06/13 08:58:13 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_str_list(char **str_list)
{
	int	index;

	index = 0;
	if (str_list == NULL)
		return ;
	while (str_list[index] != NULL)
	{
		free(str_list[index]);
		index++;
	}
	free(str_list);
}
