/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmiyazak <hmiyazak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 17:48:09 by yususato          #+#    #+#             */
/*   Updated: 2024/05/13 18:34:09 by hmiyazak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "./minishell.h"

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

// typedef enum e_redirect_type
// {
// 	UNKNOWN,
// 	QUOTE_HEREDOC,
// 	HEREDOC,
// 	IN_FILE,
// 	OUT_FILE,
// 	APPEND
// }						t_redirect_type;

// typedef struct s_token
// {
// 	t_token_kind		kind;
// 	struct s_token		*next;
// 	char				*str;
// }	t_token;

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


// bool		check_word(char	*line);
// void		remove_squote(t_token *token);
// void		remove_dquote(t_token *token);
// void		expand(t_token *token);
// bool		split_space(char **tmp, char *line);
// t_token		*split_pipe(char **tmp, char *line);
// t_token		*split_red(char **tmp, char *line);
// t_token		*split_squote(char **tmp, char *line);
// t_token		*split_dquote(char **tmp, char *line);
// t_token		*split_word(char **tmp, char *line);
// t_token		*lexer(char *line);
// bool		is_redirect(t_token *lexer_tmp);
// bool		is_quote(t_token_kind kind);
// void		cmd_init(t_token **lexer_tmp, t_parser **parser_tmp);
// void		cmd_add(t_token **lexer_tmp, t_parser **parser_tmp, char **tmp);
// void		*parser_cmd(t_token **lexer_tmp, t_parser **parser_tmp);
// void		*parser_pipe(t_parser **parser_tmp, t_parser **parser);
// t_parser	parser_node_new(void);
// void		file_init(t_file **file, char *file_name, t_token_kind kind, \
// 												t_token_kind next_kind);
// void		file_add(t_file **file, char *file_name, t_token_kind kind, \
// 												t_token_kind next_kind);
// bool		can_connect(t_token *next);
// void		node_delete(t_token *tmp, t_token *tmp_next);
// void		token_check(t_token	*lexer);
// void		*parser_check(t_token **lexer_tmp, t_parser **parser_tmp, \
// 													t_parser **parser);
// t_parser	*parser(t_token	*lexer);
// void		ft_error(void);

#endif
