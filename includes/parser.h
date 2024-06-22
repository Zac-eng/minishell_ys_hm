/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:48:09 by yususato          #+#    #+#             */
/*   Updated: 2024/06/22 21:29:30 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef enum e_token_kind
{
	TK_PIPE,
	TK_CMD,
	TK_SQUOTE,
	TK_DQUOTE,
	NOT_TK_QUOTE,
	TK_LESS,
	TK_DLESS,
	TK_GREAT,
	TK_DGREAT
}	t_token_kind;

typedef struct s_token
{
	t_token_kind		kind;
	struct s_token		*next;
	char				*str;
}	t_token;

typedef enum e_redirect_type
{
	UNKNOWN,
	QUOTE_HEREDOC,
	HEREDOC,
	IN_FILE,
	OUT_FILE,
	APPEND
}	t_redirect_type;

typedef struct s_file
{
	char				*file_name;
	t_redirect_type		type;
	struct s_file		*next;
}	t_file;

typedef struct s_parser
{
	char				**cmd;
	t_file				*file;
	struct s_parser		*next;
	struct s_parser		*prev;
}	t_parser;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

typedef enum e_code
{
	RUN_ERROR = 1,
	FILE_ERROR = 1,
	NOT_FOUND_ERROR = 127,
	NO_FILE_ERROR = 127,
	FORK_ERROR = 149,
	PARSE_ERROR = 258,
}	t_code;

bool		check_word(char	*line);
void		remove_squote(t_token *token);
void		remove_dquote(t_token *token);
void		expand(t_token *token);
bool		split_space(char **tmp, char *line);
t_token		*split_pipe(char **tmp, char *line);
t_token		*split_red(char **tmp, char *line);
t_token		*split_squote(char **tmp, char *line);
t_token		*split_dquote(char **tmp, char *line);
t_token		*split_word(char **tmp, char *line);
t_token		*lexer(char *line);
void		free_lexer(t_token *lexer_head);
t_parser	*parser(t_token	*lexer, t_env **env);
void		free_parser(t_parser *parser_head);
bool		is_redirect(t_token *lexer_tmp);
bool		is_quote(t_token_kind kind);
void		cmd_init(t_token **lexer_tmp, t_parser **parser_tmp, t_env **env);
void		cmd_add(t_token **lexer_tmp, t_parser **parser_tmp, char **tmp, t_env **env);
void		*parser_cmd(t_token **lexertmp, t_parser **parsertmp, t_env **env);
void		*parser_pipe(t_parser **parser_tmp, t_parser **parser);
t_parser	*parser_node_new(void);
void		file_init(t_file **file, char *file_name, t_token_kind kind, \
												t_token_kind next_kind);
void		file_add(t_file **file, char *file_name, t_token_kind kind, \
												t_token_kind next_kind);
void		*parser_redirect(t_token **lexer_tmp, t_parser **parser_tmp);
// bool		can_connect(t_token *next);
// void		node_delete(t_token *tmp, t_token *tmp_next);
// void		token_check(t_token	*lexer);
void		*parser_check(t_token **lexer_tmp, t_parser **parser_tmp, \
												t_parser **parser, t_env **env);
t_token		*create_token(char *line, t_token_kind kind);

#endif
