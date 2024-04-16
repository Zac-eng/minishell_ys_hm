/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 15:21:33 by yususato          #+#    #+#             */
/*   Updated: 2024/01/29 15:21:37 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_file(int fd, char *str, int len)
{
	int		byte_size;
	char	*buf;

	byte_size = 1;
	buf = (char *)ft_calloc(len + 1, MAX_SIZE);
	if (!buf)
		return (0);
	while (byte_size > 0)
	{
		byte_size = read(fd, buf, MAX_SIZE);
		if (byte_size == -1)
		{
			flag = 0;
			free(buf);
			return (0);
		}
		buf[byte_size] = '\0';
		while (buf != '\0')
		{
			if (buf == str[0])
			{
				if (strcmp(buf, str) == 0)
					return (1);
				buf++;
			}
		}
	}
	return (0);
}

void	*get_next_line(int fd, char *str)
{
	int			i;
	char		*line;
	int			len;

	len =0;
	len = ft_strlen(str);
	if (len = 0)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	i = read_file(fd, buffer, len);
	if (i == 0)
		exit(0);
	return ;
}