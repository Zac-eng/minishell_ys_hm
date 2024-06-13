/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:39:21 by yususato          #+#    #+#             */
/*   Updated: 2024/06/13 13:21:11 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
# define HEREDOC_FILE "tmp/heredoc"
static void	sigint_no_redisplay(int signum);
volatile sig_atomic_t g_interrupt = 0;

static void	sigint_no_redisplay(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

int	heredoc(t_file *file, t_env **env)
{
	int		fd;

	fd = open(HEREDOC_FILE, O_CREAT, 0644);
	close(fd);
	read_heredoc(file, env);
	fd = open(HEREDOC_FILE, O_RDONLY);
	return (fd);
}

char	*heredoc_join(char *before, char *after, char *env_str, int i)
{
	char	*new;
	char	*tmp;

	new = ft_strjoin(before, env_str);
	if (!new)
		exit(1);
	tmp = strdup(new);
	free(new);
	new = ft_strjoin(tmp, after);
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
	if (before)
		return (NULL);
	while (ft_isalnum(line[*i]) || line[*i] == '_')
		j++;
	after = ft_substr(line, *i + j, strlen(line) - (*i + j));
	if (after)
		return (NULL);
	env_name = ft_substr(line, *i, j);
	if (!(head_env = find_node(*env, env_name)))
		return (line);
	env_str = strdup(head_env->value);
	return (heredoc_join(before, after, env_str, *i + j));
}

void	write_heredoc(char *line, t_file *file, t_env **env, int fd)
{
	int		i;
	int		j;
	int		tmp;
	char	*new;

	i = 0;
	tmp = 0;
	new = strdup(line);
	while (line[i])
	{
		if (line[i] == '$')
		{
			tmp = i;
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
	write(fd, new, strlen(new));
	return ;
}

void	read_heredoc(t_file *file, t_env **env)
{
	int		fd;
	char	*line;

	printf("aaa\n");
	while (1)
	{
		line = readline("<<<<<");
		if (line == NULL)
			break ;
		if (ft_strlen(line) == 0)
		{
			break ;
		}
		else if (ft_strlen(line)
			&& !strcmp(line, "EOF"))
		{
			break ;
		}
	}

}