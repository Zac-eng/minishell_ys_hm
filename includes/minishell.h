/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yususato <yususato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 19:54:00 by hmiyazak          #+#    #+#             */
/*   Updated: 2024/02/13 18:45:11 by yususato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <limits.h>
# include <string.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h> 

# define MAX_SIZE 100

typedef enum e_token_kind
{
	TK_PIPE,
	TK_CMD,
	TK_SQUOTE,
	TK_DQUOTE,
	TK_LESS,
	TK_DLESS,
	TK_GREAT,
	TK_DGREAT
}						t_token_kind;

typedef struct s_token
{
	t_token_kind		kind;
	struct s_token		*next;
	char				*str;
}	t_token;

t_token	*lexer(char *line);
t_token	*split_word(char **tmp, char *line);
t_token	*split_dquote(char **tmp, char *line);
t_token	*split_squote(char **tmp, char *line);
t_token	*split_red(char **tmp, char *line);
t_token	*split_pipe(char **tmp, char *line);
bool	split_space(char **tmp, char *line);
t_token	*create_token(char *line, t_token_kind kind);
bool	check_word(char	*line);



#endif