/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 19:54:00 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/05/20 20:01:19 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <limits.h>
# include <string.h>
# include <sys/stat.h>
# include "parser.h"
# include "../libft/libft.h"

# define MAX_SIZE 100

void	signalctrl(void);
void	put_error_exit(const char *error);
void	handle_status(int *status);
void	execute(char *line, t_env **env);
t_token	*lexer(char *line);
t_env	*get_key_value(char *env_line);
void	*free_env(t_env *env);
void	free_node(t_env *node);
t_env	*env_into_tenv(char **env);
void	_cd(char **cmd);
void	_echo(char **cmd);
void	_env(t_env *env);
void	_export(char **cmd, t_env **env_head);
void	_pwd(void);
void	_unset(char **cmd, t_env **env);
int		is_equal(char *str, char *ref);

#endif