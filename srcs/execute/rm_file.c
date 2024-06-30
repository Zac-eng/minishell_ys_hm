
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rm_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 18:16:09 by yususato          #+#    #+#             */
/*   Updated: 2024/06/17 19:47:24 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	rm_heredoc_file(void)
{
	int		i;
	char	*file;
	char	*tmp;

	i = 0;
	tmp = ft_itoa(i);
	file = ft_strjoin(HEREDOC_FILE, tmp);
	free(tmp);
	while (!access(file, F_OK))
	{
		unlink(file);
		free(file);
		i++;
		tmp = ft_itoa(i);
		if (tmp == NULL)
			exit(1);
		file = ft_strjoin(HEREDOC_FILE, tmp);
		if (file == NULL)
			exit(1);
	}
	return ;
}
