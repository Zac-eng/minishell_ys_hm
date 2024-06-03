/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 19:54:00 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/05/31 16:24:16 by hmiyazak         ###   ########.fr       */
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

void	signalctrl(void);
void	sigexit(int signum);
void	put_error_exit(const char *error);
void	handle_status(int *status);
void	execute(t_parser *current, t_env **env, char **paths);
void	execute_cmd(char **cmd, t_env **env, char **paths);
void	execute_redirect(t_parser *cmd, t_env **env, char **paths);
int		execute_path(char **cmd, char **env);
t_token	*lexer(char *line);
t_env	*get_key_value(char *env_line);
char	**get_paths(void);
void	free_str_list(char **str_list);
void	*free_env(t_env *env);
void	free_node(t_env *node);
t_env	*env_into_tenv(char **env);
char	**env_into_list(t_env *env);
void	_cd(char **cmd);
void	_echo(char **cmd);
void	_env(t_env *env);
void	_export(char **cmd, t_env **env_head);
void	_pwd(void);
void	_unset(char **cmd, t_env **env);
int		is_equal(char *str, char *ref);

#endif