/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:16:38 by yususato          #+#    #+#             */
/*   Updated: 2024/03/12 21:07:43 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	pwd(void)
{
	char	path[PATH_MAX];

	if (getcwd(path, sizeof(path)) != NULL)
		ft_printf("%s\n", path);
	else
		perror("Error\n");
	return ;
}



void	echo_n(int ac, char **av)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		printf("%s",argv[i]);
		i++;
	}
}
