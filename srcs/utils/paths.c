/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/20 22:27:58 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/05/20 22:38:54 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_paths(void)
{
	char	**path_list;
	char	*path_line;

	path_line = getenv("PATH");
	if (path_line == NULL)
		exit(1);
	path_list = ft_split(path_line, ':');
	if (path_list == NULL)
		exit(1);
	return (path_list);
}

void	free_paths(char **paths)
{
	int	index;

	index = 0;
	if (paths == NULL)
		return ;
	while (paths[index] != NULL)
	{
		free(paths[index]);
		index++;
	}
	free(paths);
}
