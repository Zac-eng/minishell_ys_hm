/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 19:54:00 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/05/13 18:34:17 by hmiyazak         ###   ########.fr       */
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
# include "./parser.h"
# include "../libft/libft.h"

# define MAX_SIZE 100

// typedef enum e_token_kind
// {
// 	TK_PIPE,
// 	TK_CMD,
// 	TK_SQUOTE,
// 	TK_DQUOTE,
// 	TK_LESS,
// 	TK_DLESS,
// 	TK_GREAT,
// 	TK_DGREAT
// }						t_token_kind;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

// typedef struct s_token
// {
// 	t_token_kind		kind;
// 	struct s_token		*next;
// 	char				*str;
// }	t_token;

// typedef enum e_redirect_type
// {
// 	UNKNOWN,
// 	QUOTE_HEREDOC,
// 	HEREDOC,
// 	IN_FILE,
// 	OUT_FILE,
// 	APPEND
// }						t_redirect_type;

// typedef struct s_file
// {
// 	char				*file_name;
// 	t_redirect_type		type;
// 	struct s_file		*next;
// }						t_file;

// typedef struct s_parser
// {
// 	char				**cmd;
// 	t_file				*file;
// 	struct s_parser		*next;
// 	struct s_parser		*prev;
// }	t_parser;

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