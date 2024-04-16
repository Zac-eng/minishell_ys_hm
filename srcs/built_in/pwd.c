/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 17:16:38 by yususato          #+#    #+#             */
/*   Updated: 2023/12/22 19:50:44 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	pwd(void)
{
	char	path[PATH_MAX];

	if (getcwd(path, sizeof(path)) != NULL)
		ft_printf("%s\n", path);
	else
		ft_printf("Error\n");
	return ;
}

void	cd(char *path)
{
	if (chrdir(path) == -1)
		ft_printf("Error\n");
	return ;
}

void	export(char	*name, char *value)
{
	if (setenv(name, value, 1) != 0)
		perroer("Error\n");
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

void	unset(char *name)
{
	if (unsetev(name) != 0)
		perror("Error\n");
}
