#include "minishell.h"
# define HEREDOC_FILE "tmp/heredoc"

int	heredog(t_file *file, t_env **env)
{
	int		fd;
	char	*line;

	fd = open(HEREDOC_FILE, O_CREAT, 0644);
	close(fd);
	read_heredoc(file, env);
	fd = open(HEREDOC_FILE, O_RDONLY);
	return (fd);
}

bool	parser_env(t_token **lexer_tmp, t_parser **parser_tmp, t_env **env)
{
	t_env	*head_env;

	if (!(head_env = find_node(*env, (&(*lexer_tmp)->str[1]))))
		return (false);
	(*parser_tmp)->cmd[0] = strdup(head_env->value);
	return (true);
}

char	*heeredoc_join(char *before, char *after, char *env_str, int i)
{
	char	*new;

	new = strjoin(before, env_str);
	if (!new)
		exit(1);
	new = strjoin(new, after);
}

void	env_heredoc(char *line, t_file *file, t_env **env, int i)
{
	int		j;
	char	*new;
	char	*before;
	char	*after;
	char	*env_name;
	char	*env_str;
	t_env	*head_env;

	j = 0;
	before = substr(line, 0, i);
	if (before)
		return (NULL);
	while (is_alnum(line) || line[i] == '_')
		j++;
	after = substr(line, i + j, strlen(line) - (i + j));
	if (after)
		return (NULL);
	env_name = substr(line, i, j);
	if (!(head_env = find_node(*env, env_name)))
		return ;
	env_str = strdup(head_env->value);
	return (heredoc_join(before, after, env_str, i));
}

int	write_heredog(char *line,t_file *file, t_env **env)
{
	int		i;
	char	*new;

	i = 0;
	while (line[i])
	{
		if (line[i] == "$")
		{
			new = env_heredoc(line, file, env, i)
		}
		else
		{
			new[i] = line[i]
		}
		i++;
	}

}

void	read_heredoc(t_file *file, t_env **env)
{
	char	*line;

	while (1)
	{
		fd = open(HEREDOC_FILE, O_WRONLY | O_APPEND, 0644);
		line = readluine("> ");
		if (!line)
			return (NULL);
		write_heredoc(line, file, env);
		close(fd);
	}
}