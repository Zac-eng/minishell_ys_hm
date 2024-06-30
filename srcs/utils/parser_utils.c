/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/23 20:04:19 by yususato          #+#    #+#             */
/*   Updated: 2024/06/26 19:25:02 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	is_squote_space(char *str)
{
	int	len;

	len = 0;
	while (str[len] && str[len] != ' ' &&  str[len] != '\'')
		len++;
	return (len);
}

void	str_insert(char	*new, char *str)
{
	int	len;

	len = 0;
	while (str[len])
	{
		new[len] = str[len];
		len++;
	}
	return ;
}
