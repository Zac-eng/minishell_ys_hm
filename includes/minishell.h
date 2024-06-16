/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 19:54:00 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/06/16 19:12:06 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <limits.h>
# include <string.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "parser.h"
# include "../libft/libft.h"

extern volatile sig_atomic_t	g_status;

void	signalctrl(void);
void	sigexit(int signum);
char	**get_paths(t_env *env);
t_env	*env_into_tenv(char **env);
char	**env_into_list(t_env *env);
void	execute(char *line, t_env **env, char **paths);
void	execute_cmd(char **cmd, t_env **env, char **paths);
void	execute_envpath(char **paths, char **cmd, char **env);
void	execute_redirect(t_parser *cmd, t_env **env, char **paths);
void	_cd(char **cmd, t_env *env);
void	_echo(char **cmd);
void	_env(t_env *env);
void	_export(char **cmd, t_env **env_head);
void	_pwd(char **cmd);
void	_unset(char **cmd, t_env **env);
void	minishell_exit(char **cmd);
t_env	*create_envnode(char *env_line);
void	free_env(t_env *env);
void	free_node(t_env *node);
void	free_str_list(char **str_list);
t_env	*find_node(t_env *env_head, char *key);
void	push_env(t_env *env_head, t_env *new_node);
int		remove_env(t_env *previous);
char	*_getenv(t_env *env_head, char *key);
void	put_error(t_code error_code, char *insert);
void	put_error_exit(t_code error_code);
void	handle_status(void);
int		is_equal(char *str, char *ref);
int		heredoc(t_file *file, t_env **env);
char	*heredoc_join(char *before, char *after, char *env_str, int *i);
char	*env_heredoc(char *line, t_file *file, t_env **env, int *i);
void	write_heredoc(char *line, t_file *file, t_env **env, int fd);
void	read_heredoc(t_file *file, t_env **env);
int		quote_heredoc(t_file *file, t_env **env);
void	quote_read_heredoc(t_file *file, t_env **env);

#endif