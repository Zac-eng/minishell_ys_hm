/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:16:38 by yususato          #+#    #+#             */
/*   Updated: 2024/04/21 14:59:14 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd(void)
{
	char	path[PATH_MAX];

	if (getcwd(path, sizeof(path)) != NULL)
		ft_printf("%s\n", path);
	else
		perror("Error\n");
	return ;
}



void	echo_n(int argc, char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		printf("%s",argv[i]);
		i++;
	}
}
