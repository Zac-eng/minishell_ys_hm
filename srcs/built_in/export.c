/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 21:07:07 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/03/13 09:54:47 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	export(char	*name, char *value)
{
	if (setenv(name, value, 1) != 0)
		perroer("Error\n");
}
