/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 12:44:33 by h.miyazaki        #+#    #+#             */
/*   Updated: 2024/05/30 11:44:14 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	create_absolute(char *buffer, char *dest);
static int	add_path(char *dest, char *src, int max_len);

void	_cd(char **cmd)
{
	char	absolute_path[PATH_MAX];
	char	*destination;

	if (cmd == NULL || cmd[0] == NULL)
		return ;
	ft_bzero(&absolute_path[0], PATH_MAX);
	destination = cmd[1];
	if (destination == NULL)
		destination = "~";
	if (*destination == '~')
	{
		create_absolute(&absolute_path[0], destination);
		if (chdir(absolute_path) != 0)
			printf("cd: no such file or directory: %s\n", destination);
	}
	else
	{
		if (chdir(destination) != 0)
			printf("cd: no such file or directory: %s\n", destination);
	}
}

static void	create_absolute(char *buffer, char *dest)
{
	char	*home;
	int		i;

	i = 0;
	if (*dest != '~')
		return ;
	home = getenv("HOME");
	if (home == NULL)
		return ;
	i += add_path(&buffer[i], home, PATH_MAX - i);
	if (i == -1)
	{
		ft_bzero(buffer, PATH_MAX);
		return ;
	}
	i += add_path(&buffer[i], &dest[1], PATH_MAX - i);
	if (i == -1)
	{
		ft_bzero(buffer, PATH_MAX);
		return ;
	}
	buffer[i] = '\0';
}

static int	add_path(char *dest, char *src, int max_len)
{
	int	i;

	i = 0;
	if (dest == NULL || src == NULL)
		return (-1);
	while (src[i] && i < max_len)
	{
		dest[i] = src[i];
		i++;
	}
	return (i);
}
