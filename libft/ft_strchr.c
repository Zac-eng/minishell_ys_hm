/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/19 12:07:20 by yususato          #+#    #+#             */
/*   Updated: 2023/11/20 16:18:31 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if (c == '\0')
		return ((char *)s);
	return (NULL);
}

int main()
{
	char c[] = "abc.ber";
	char d = '.';
	char *a;

	a = strrchr(c,d);
	if (a != NULL)
	{
		if (strncmp(a,".ber",5) != 0)
		;
	}
	exit(1);
	
	
}

