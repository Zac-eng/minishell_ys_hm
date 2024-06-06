/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 19:54:00 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/06/06 10:59:44 by hmiyazak         ###   ########.fr       */
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
char	**get_paths(void);
t_env	*env_into_tenv(char **env);
char	**env_into_list(t_env *env);
void	execute(char *line, t_env **env, char **paths);
void	execute_cmd(char **cmd, t_env **env, char **paths);
void	execute_redirect(t_parser *cmd, t_env **env, char **paths);
void	_cd(char **cmd);
void	_echo(char **cmd);
void	_env(t_env *env);
void	_export(char **cmd, t_env **env_head);
void	_pwd(void);
void	_unset(char **cmd, t_env **env);
t_env	*create_envnode(char *env_line);
void	*free_env(t_env *env);
void	free_node(t_env *node);
void	free_str_list(char **str_list);
t_env	*find_node(t_env *env_head, char *key);
void	push_env(t_env *env_head, t_env *new_node);
int		remove_env(t_env *previous);
void	put_error_exit(const char *error);
void	handle_status(int *status);
int		is_equal(char *str, char *ref);

#endif