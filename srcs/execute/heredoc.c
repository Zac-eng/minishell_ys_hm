/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:39:21 by yususato          #+#    #+#             */
/*   Updated: 2024/06/13 23:09:14 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
# define HEREDOC_FILE "srcs/execute/tmp/heredoc"

int	heredoc(t_file *file, t_env **env)
{
	int		fd;

	fd = open(HEREDOC_FILE, O_CREAT, 0644);
	printf("%d\n", fd);
	close(fd);
	read_heredoc(file, env);
	fd = open(HEREDOC_FILE, O_RDONLY);
	return (fd);
}

char	*heredoc_join(char *before, char *after, char *env_str, int *i)
{
	char	*new;
	char	*tmp;

	printf("i:%d\n", *i);
	new = ft_strjoin(before, env_str);
	if (!new)
		exit(1);
	tmp = strdup(new);
	free(new);
	new = ft_strjoin(tmp, after);
	*i = strlen(before) + strlen(env_str);
	return (new);
}

char	*env_heredoc(char *line, t_file *file, t_env **env, int *i)
{
	int		j;
	char	*new;
	char	*before;
	char	*after;
	char	*env_name;
	char	*env_str;
	t_env	*head_env;

	j = 0;
	before = ft_substr(line, 0, *i);
	if (!before)
		return (NULL);
		
	while (ft_isalnum(line[*i + j]) || line[*i + j] == '_')
		j++;
	after = ft_substr(line, *i + j, strlen(line) - (*i + j));
	if (!after)
		return (NULL);
	env_name = ft_substr(line, *i, j);
	head_env = find_node(*env, env_name);
	if (!head_env)
		return (line);
	env_str = strdup(head_env->value);
	printf("env_str%s\n",env_str);
	printf("j:%d",j);
	printf("aa\n");
	*i = *i + j;
	return (heredoc_join(before, after, env_str, i));
}

void	write_heredoc(char *line, t_file *file, t_env **env, int fd)
{
	int		i;
	int		j;
	int		tmp;
	char	*new;

	i = 0;
	j = 0;
	tmp = 0;
	new = strdup(line);
	while (line[i])
	{
		if (line[i++] == '$')
		{
			tmp = i;
			new = env_heredoc(line, file, env, &i);
			printf("new:%s\n",new);
			j = i;
			i = tmp;
		}
		else
		{
			new[j] = line[i];
		}
		i++;
		j++;
	}
			printf("new2:%s\n",new);
	printf("i:%d,j:%d\n",i,j);
	write(fd, new, strlen(new));
	write(fd, "\n", 1);
	return ;
}

void	read_heredoc(t_file *file, t_env **env)
{
	int		fd;
	char	*line;

	while (true)
	{
		fd = open(HEREDOC_FILE, O_WRONLY | O_APPEND, 0644);
		if (fd == -1)
			exit(1);
		line = readline("> ");
		if (!line)
			break ;
		if (ft_strlen(line) == 0 && ft_strlen(file->file_name))
		{
			// free_close(line, fd);
			break ;
		}
		else if (ft_strlen(line) && !strcmp(line, file->file_name))
		{
			// free_close(line, fd);
			break ;
		}
		write_heredoc(line, file, env, fd);
		close(fd);
	}
}
