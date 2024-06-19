/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:39:21 by yususato          #+#    #+#             */
/*   Updated: 2024/06/19 23:39:34 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc(t_file *file, t_env **env)
{
	int		fd;
	char	*new_file;

	new_file = create_file();
	read_heredoc(file, env, new_file);
	fd = open(new_file, O_RDONLY);
	close(fd);
	filename_change(&file, new_file);
	return ;
}

char	*create_file(void)
{
	int		i;
	int		fd;
	char	*new;
	char	*tmp;

	fd = 0;
	i = 0;
	tmp = ft_itoa(i);
	new = ft_strjoin(HEREDOC_FILE, tmp);
	if (new == NULL)
		exit(1);
	free(tmp);
	if (new == NULL)
		exit(1);
	while (!access(new, F_OK))
	{
		i++;
		free(new);
		tmp = ft_itoa(i);
		if (tmp == NULL)
			exit(1);
		new = ft_strjoin(HEREDOC_FILE, tmp);
		if (new == NULL)
			exit(1);
		free(tmp);
	}
	fd = open(new, O_CREAT, 0644);
	close(fd);
	return (new);
}

char	*heredoc_join(char *before, char *after, char *env_str, int *i)
{
	char	*new;
	char	*tmp;

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
		if (line[i] == '$')
		{
			tmp = i;
			i++;
			new = env_heredoc(line, file, env, &i);
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
	new[j] = line[i];
	write(fd, new, strlen(new));
	write(fd, "\n", 1);
	return ;
}


void	free_close(char *line, int fd)
{
	free(line);
	close(fd);
}

void	read_heredoc(t_file *file, t_env **env, char *new_file)
{
	int		fd;
	char	*line;

	while (true)
	{
		fd = open(new_file, O_WRONLY | O_APPEND, 0644);
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
