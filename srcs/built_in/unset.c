/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 21:07:32 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/03/12 21:07:53 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	unset(char *name)
{
	if (unsetev(name) != 0)
		perror("Error\n");
}