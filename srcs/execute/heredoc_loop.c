/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/05 22:02:05 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/07/07 15:00:02 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_loop(t_file *file, t_env **env)
{
	t_file	*current;

	current = file;
	while (current != NULL)
	{
		if (current->type == HEREDOC)
		{
			heredoc(current, env);
		}
		else if (current->type == QUOTE_HEREDOC)
		{
			quote_heredoc(current);
		}
		current = current->next;
	}
}
